# Swisstrain Terrain Bounding Box and Coordinate System

## Overview

This document describes the specific bounding box coordinates used for the Swisstrain terrain prototype and provides information about the coordinate system.

## Bounding Box Definition

The target area for the Swisstrain terrain prototype is defined using the Swiss coordinate system EPSG:2056 (CH1903+/LV95):

### Coordinates (EPSG:2056)
- **Top-left corner**: 2673957.58, 1216900.00
- **Bottom-right corner**: 2689486.72, 1204462.45

### Dimensions
- **Width**: 15,529.14 meters (Easting)
- **Height**: 12,437.55 meters (Northing)

## Coordinate System Information

### EPSG:2056 - Swiss CH1903+/LV95

The Swiss coordinate system (CH1903+/LV95) is specifically designed for Switzerland and Liechtenstein:

- **Coordinate System Type**: Cartesian 2D
- **Axes**: Easting (E) and Northing (N)
- **Units**: Meters
- **Area of Use**: Switzerland and Liechtenstein
- **Scope**: Cadastre, engineering survey, topographic mapping (large and medium scale)

### Key Properties

1. **Projection Method**: Hotine Oblique Mercator
2. **Datum**: CHTRS95 (Swiss Terrestrial Reference System 1995)
3. **Ellipsoid**: GRS 1980
4. **Prime Meridian**: Greenwich

### Transformation to WGS84

To convert to the more commonly used WGS84 coordinate system:

- **Transformation Method**: Geocentric translations (geog2D domain)
- **Remarks**: Parameter values are from CH1903+ to ETRS89 (1) assuming that ETRS89 is equivalent to WGS 84

## Approximate Geographic Location

While the precise conversion requires specialized tools, the bounding box roughly corresponds to:

- **Approximate Center**: 47.1°N, 9.3°E
- **Region**: Eastern Switzerland, likely near the canton of St. Gallen or Appenzell

This area provides representative Swiss topography including:
- Alpine mountain ranges
- Valleys
- Lakes
- Varied elevation changes
- Representative Swiss landscape features

## Data Processing Considerations

When processing terrain data for this bounding box:

1. **Data Resolution**: Based on the area size, appropriate DEM resolutions would be:
   - For detailed work: swissALTI3D (0.5m or 2m)
   - For general use: DHM25 (approximately 25m)
   - For testing: DHM25/200m (200m)

2. **File Size Estimates**: 
   - At 0.5m resolution: ~1.5 billion points
   - At 2m resolution: ~96 million points
   - At 25m resolution: ~614,000 points

3. **Recommended Processing Resolution for Unreal Engine**:
   - Target 1025x1025 to 4097x4097 pixels for good balance of detail and performance
   - This provides resolution of approximately 3-15 meters per pixel

## Unreal Engine Integration

### Scale Settings

When importing into Unreal Engine:

- **World Scale**: 1 unit = 1 meter (Unreal default)
- **Landscape Scale X**: ~7.6 (15529.14m / 2049 pixels)
- **Landscape Scale Y**: ~6.1 (12437.55m / 2049 pixels)
- **Coordinate Alignment**: Ensure Unreal world coordinates align with swisstopo coordinates

### Height Scale

Elevation values in swisstopo data are in meters above sea level. For Unreal Engine:
- **Minimum Z**: Should match the minimum elevation in the dataset
- **Maximum Z**: Should match the maximum elevation in the dataset
- **Vertical Exaggeration**: May be applied artistically (typically 1.0-3.0x)

## References

1. Federal Office of Topography swisstopo: https://www.swisstopo.admin.ch/
2. EPSG:2056 Information: https://epsg.io/2056
3. Swiss Coordinate System Documentation: https://www.swisstopo.admin.ch/en/swiss-coordinate-system