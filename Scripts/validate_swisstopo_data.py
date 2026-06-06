#!/usr/bin/env python3
"""Validate swisstopo/terrain source files and generated RAW heightmaps.

Examples:
    python Scripts/validate_swisstopo_data.py input.asc --type asc
    python Scripts/validate_swisstopo_data.py Content/Landscape/Heightmaps/processed_heightmap.raw --type raw --size 2049x2049
"""

from __future__ import annotations

import argparse
import json
import math
from pathlib import Path
from typing import Any, Dict, Tuple

import numpy as np


REQUIRED_ASC_FIELDS = ["ncols", "nrows", "cellsize"]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Validate swisstopo ASCII grid files and generated RAW heightmaps.")
    parser.add_argument("input_file", help="File to validate")
    parser.add_argument("--type", choices=["auto", "asc", "raw"], default="auto", help="Input file type")
    parser.add_argument("--size", help="Required for RAW validation when size cannot be inferred, e.g. 2049x2049")
    return parser.parse_args()


def infer_type(path: Path, forced: str) -> str:
    if forced != "auto":
        return forced
    return "asc" if path.suffix.lower() == ".asc" else "raw"


def parse_size(size: str | None, item_count: int) -> Tuple[int, int]:
    if size:
        try:
            w_str, h_str = size.lower().split("x", 1)
            return int(w_str), int(h_str)
        except Exception as exc:
            raise ValueError(f"Invalid --size value: {size!r}") from exc
    root = int(math.isqrt(item_count))
    if root * root != item_count:
        raise ValueError("RAW dimensions could not be inferred; provide --size WIDTHxHEIGHT")
    return root, root


def validate_ascii_grid(path: Path) -> Dict[str, Any]:
    result: Dict[str, Any] = {"valid": True, "errors": [], "warnings": [], "metadata": {}, "stats": {}}
    with path.open("r", encoding="utf-8") as fh:
        header = [fh.readline().strip() for _ in range(6)]
        metadata: Dict[str, float] = {}
        for line in header:
            parts = line.split()
            if len(parts) < 2:
                result["errors"].append(f"Invalid header line: {line!r}")
                result["valid"] = False
                continue
            key = parts[0].lower()
            value = parts[-1]
            try:
                metadata[key] = float(value)
            except ValueError:
                result["errors"].append(f"Invalid numeric value for {key}: {value!r}")
                result["valid"] = False
        for field in REQUIRED_ASC_FIELDS:
            if field not in metadata:
                result["errors"].append(f"Missing required field: {field}")
                result["valid"] = False
        if not result["valid"]:
            result["metadata"] = metadata
            return result
        ncols = int(metadata["ncols"])
        nrows = int(metadata["nrows"])
        data = np.loadtxt(fh, dtype=np.float32)
    if data.shape != (nrows, ncols):
        result["errors"].append(f"Expected raster shape {(nrows, ncols)}, got {data.shape}")
        result["valid"] = False
    if np.isnan(data).any():
        result["warnings"].append("Raster contains NaN values")
    result["metadata"] = metadata
    result["stats"] = {
        "shape": [int(v) for v in data.shape],
        "min": float(np.min(data)),
        "max": float(np.max(data)),
        "mean": float(np.mean(data)),
    }
    return result


def validate_raw_heightmap(path: Path, size_arg: str | None) -> Dict[str, Any]:
    result: Dict[str, Any] = {"valid": True, "errors": [], "warnings": [], "metadata": {}, "stats": {}}
    data = np.fromfile(path, dtype="<u2")
    if data.size == 0:
        result["errors"].append("RAW file is empty")
        result["valid"] = False
        return result
    try:
        width, height = parse_size(size_arg, int(data.size))
    except ValueError as exc:
        result["errors"].append(str(exc))
        result["valid"] = False
        return result
    if width * height != data.size:
        result["errors"].append(f"Size mismatch: {width}x{height} != {data.size} samples")
        result["valid"] = False
        return result
    reshaped = data.reshape((height, width))
    result["metadata"] = {"width": width, "height": height, "dtype": "uint16-le"}
    result["stats"] = {
        "min": int(np.min(reshaped)),
        "max": int(np.max(reshaped)),
        "mean": float(np.mean(reshaped)),
    }
    if int(np.min(reshaped)) == int(np.max(reshaped)):
        result["warnings"].append("Heightmap is constant; terrain would be flat")
    return result


def main() -> int:
    args = parse_args()
    path = Path(args.input_file)
    file_type = infer_type(path, args.type)
    result = validate_ascii_grid(path) if file_type == "asc" else validate_raw_heightmap(path, args.size)
    print(json.dumps(result, indent=2))
    return 0 if result.get("valid") else 1


if __name__ == "__main__":
    raise SystemExit(main())
