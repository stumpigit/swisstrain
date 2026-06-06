#!/usr/bin/env python3
"""Convert swisstopo/ESRI ASCII grid elevation data to Unreal-friendly RAW heightmaps.

Example:
    python Scripts/process_swisstopo_data.py input.asc Content/Landscape/Heightmaps/ --width 2049 --height 2049
"""

from __future__ import annotations

import argparse
import json
import math
import struct
import zlib
from pathlib import Path
from typing import Dict, Tuple

import numpy as np


HEADER_KEYS = {
    "ncols": int,
    "nrows": int,
    "xllcorner": float,
    "yllcorner": float,
    "xllcenter": float,
    "yllcenter": float,
    "cellsize": float,
    "nodata_value": float,
}


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Convert swisstopo/ESRI ASCII grid data into Unreal-compatible 16-bit R16 heightmaps."
    )
    parser.add_argument("input_file", help="Path to input ASCII grid (.asc) file")
    parser.add_argument("output_dir", help="Directory for generated RAW + metadata files")
    parser.add_argument("--width", type=int, help="Target output width in pixels")
    parser.add_argument("--height", type=int, help="Target output height in pixels")
    parser.add_argument(
        "--output-name",
        default="processed_heightmap",
        help="Base filename for outputs without extension (default: processed_heightmap)",
    )
    parser.add_argument(
        "--z-scale",
        type=float,
        default=1.0,
        help="Optional multiplicative scale applied before normalization (default: 1.0)",
    )
    return parser.parse_args()


def read_ascii_grid(path: Path) -> Tuple[Dict[str, float], np.ndarray]:
    metadata: Dict[str, float] = {}
    header_lines = []
    with path.open("r", encoding="utf-8") as fh:
        for _ in range(6):
            line = fh.readline()
            if not line:
                raise ValueError("ASCII grid header is incomplete")
            header_lines.append(line.strip())
        for line in header_lines:
            parts = line.split()
            if len(parts) < 2:
                raise ValueError(f"Invalid header line: {line!r}")
            key = parts[0].lower()
            value = parts[-1]
            caster = HEADER_KEYS.get(key, float)
            metadata[key] = caster(value)
        ncols = int(metadata["ncols"])
        nrows = int(metadata["nrows"])
        data = np.loadtxt(fh, dtype=np.float32)
    if data.shape != (nrows, ncols):
        raise ValueError(f"Expected raster shape {(nrows, ncols)}, got {data.shape}")
    return metadata, data


def fill_nodata(data: np.ndarray, nodata_value: float | None) -> np.ndarray:
    filled = data.copy()
    if nodata_value is None:
        return filled
    mask = filled != nodata_value
    if not np.any(mask):
        raise ValueError("Raster contains only NODATA values")
    min_valid = float(np.min(filled[mask]))
    filled[~mask] = min_valid
    return filled


def bilinear_resize(data: np.ndarray, target_h: int, target_w: int) -> np.ndarray:
    src_h, src_w = data.shape
    if (src_h, src_w) == (target_h, target_w):
        return data.copy()

    y = np.linspace(0, src_h - 1, target_h)
    x = np.linspace(0, src_w - 1, target_w)
    x0 = np.floor(x).astype(int)
    y0 = np.floor(y).astype(int)
    x1 = np.clip(x0 + 1, 0, src_w - 1)
    y1 = np.clip(y0 + 1, 0, src_h - 1)
    xw = x - x0
    yw = y - y0

    top = (1.0 - xw)[None, :] * data[y0][:, x0] + xw[None, :] * data[y0][:, x1]
    bottom = (1.0 - xw)[None, :] * data[y1][:, x0] + xw[None, :] * data[y1][:, x1]
    resized = (1.0 - yw)[:, None] * top + yw[:, None] * bottom
    return resized.astype(np.float32)


def normalize_to_uint16(data: np.ndarray, z_scale: float) -> Tuple[np.ndarray, Dict[str, float]]:
    scaled = data.astype(np.float32) * np.float32(z_scale)
    min_val = float(np.min(scaled))
    max_val = float(np.max(scaled))
    if math.isclose(min_val, max_val):
        raise ValueError("Cannot normalize constant-height terrain")
    normalized = (scaled - min_val) / (max_val - min_val)
    raw = np.round(normalized * 65535.0).astype("<u2")
    stats = {
        "min_elevation": min_val,
        "max_elevation": max_val,
        "elevation_range": max_val - min_val,
    }
    return raw, stats


def _png_chunk(chunk_type: bytes, data: bytes) -> bytes:
    return (
        struct.pack(">I", len(data))
        + chunk_type
        + data
        + struct.pack(">I", zlib.crc32(chunk_type + data) & 0xFFFFFFFF)
    )


def write_png16_grayscale(path: Path, data: np.ndarray) -> None:
    if data.dtype != np.dtype("<u2"):
        raise ValueError("PNG writer expects uint16 little-endian source data")
    height, width = data.shape
    be = data.astype(">u2", copy=False)
    scanlines = b"".join(b"\x00" + be[row].tobytes() for row in range(height))
    compressed = zlib.compress(scanlines, level=9)
    ihdr = struct.pack(">IIBBBBB", width, height, 16, 0, 0, 0, 0)
    png = b"\x89PNG\r\n\x1a\n" + _png_chunk(b"IHDR", ihdr) + _png_chunk(b"IDAT", compressed) + _png_chunk(b"IEND", b"")
    path.write_bytes(png)


def main() -> int:
    args = parse_args()
    input_path = Path(args.input_file)
    output_dir = Path(args.output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    metadata, data = read_ascii_grid(input_path)
    data = fill_nodata(data, metadata.get("nodata_value"))

    target_w = args.width or int(metadata["ncols"])
    target_h = args.height or int(metadata["nrows"])
    if target_w <= 0 or target_h <= 0:
        raise ValueError("Target width/height must be positive")

    resized = bilinear_resize(data, target_h, target_w)
    raw, stats = normalize_to_uint16(resized, args.z_scale)

    base = output_dir / args.output_name
    raw_path = base.with_suffix(".r16")
    png_path = base.with_suffix(".png")
    meta_path = base.with_suffix(".json")

    raw.tofile(raw_path)
    write_png16_grayscale(png_path, raw)
    payload = {
        "source_file": str(input_path),
        "output_r16": str(raw_path),
        "output_png": str(png_path),
        "output_size": {"width": target_w, "height": target_h},
        "source_metadata": metadata,
        "stats": stats,
        "unreal_notes": {
            "preferred_import": str(png_path),
            "alternate_import": str(raw_path),
            "format": "16-bit grayscale PNG and 16-bit grayscale r16",
            "import_width": target_w,
            "import_height": target_h,
        },
    }
    meta_path.write_text(json.dumps(payload, indent=2), encoding="utf-8")

    print(f"Wrote {raw_path}")
    print(f"Wrote {png_path}")
    print(f"Wrote {meta_path}")
    print(f"Output size: {target_w}x{target_h}")
    print(f"Elevation range: {stats['min_elevation']:.2f} .. {stats['max_elevation']:.2f}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
