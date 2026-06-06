# Swisstopo Data Access and Processing for Unreal Engine

## Overview

This document describes the process for acquiring and processing swisstopo digital height model (DHM) data for use in Unreal Engine 5. Our target area is defined in the swisstopo coordinate system EPSG:2056 with specific bounding box coordinates.

## Swisstopo Data Products

### Available Data Products

1. **swissALTI3D** - Extremely precise digital elevation model (0.5m or 2m resolution)
   - Best quality for detailed terrain representation
   - Covers the entire surface of Switzerland without vegetation and development
   - Available in 1km² tiles

2. **DHM25** - Digital height model based on 1:25'000 Swiss national map
   - Good balance of quality and file size
   - Represents earth's surface without vegetation and buildings
   - Grid resolution appropriate for our use case

3. **DHM25 / 200m** - Light version of DHM25
   - Lower resolution but smaller file sizes
   - Suitable for testing and prototyping

## Target Area Definition

Coordinates in EPSG:2056 (Swiss CH1903+/LV95):
- **Top-left**: 2673957.58, 1216900.00
- **Bottom-right**: 2689486.72, 1204462.45
- **Width**: 15529.14 meters
- **Height**: 12437.55 meters

## Data Access Process

### 1. Access via Free Geodata Portal

Swisstopo offers official geodata under Open Government Data (OGD) principles:

1. Visit the swisstopo free geodata portal: https://shop.swisstopo.admin.ch/en/free-geodata
2. Navigate to the height models section
3. Select DHM25 for optimal quality/file size balance
4. Use the interactive interface to select the area within our bounding box
5. Download in ESRI ASCII GRID format for easy processing

### 2. Direct Download Options

1. **swissALTI3D**: Available for direct download but requires registering and agreeing to terms
2. **DHM25**: Available through the swisstopo download interface
3. **DHM25/200m**: Available for immediate download for testing purposes

## Data Processing Pipeline

### Step 1: Data Format Conversion

Unreal Engine supports several heightmap formats:
- RAW 16-bit
- PNG 16-bit
- JPG (less precise)

For swisstopo data in ESRI ASCII GRID format:

1. Parse the ASCII grid header for:
   - NCOLS (width)
   - NROWS (height)
   - XLLCORNER (bottom-left X coordinate)
   - YLLCORNER (bottom-left Y coordinate)
   - CELLSIZE (resolution in meters)
   - NODATA_VALUE (value for missing data)

2. Extract the elevation data (grid of values)

3. Convert to Unreal Engine compatible format:
   - Scale values to appropriate range (0-65535 for 16-bit)
   - Ensure proper orientation (swisstopo data may need flipping)
   - Save as RAW 16-bit or PNG 16-bit

### Step 2: Resolution Adjustment

Determine appropriate resolution for Unreal Engine landscape:
- Unreal Engine landscapes work best with power-of-2 dimensions + 1
- Example: 513x513, 1025x1025, 2049x2049, 4097x4097
- Higher resolution = more detail but larger files and potential performance impact

### Step 3: Data Validation

Before import:
1. Check for missing data values (NODATA areas)
2. Verify coordinate system alignment
3. Confirm elevation range is appropriate
4. Validate that processed files match Unreal Engine requirements

## Implementation Plan

### Immediate Actions (Can be done now):

1. Document the complete swisstopo data acquisition workflow
2. Create scripts for automatic processing of downloaded data
3. Set up sample data for testing (using DHM25/200m for quick tests)
4. Create documentation for Unreal Engine import process

### Prerequisites Before Full Implementation:

1. Install Unreal Engine 5.5
2. Acquire actual swisstopo data for our bounding box
3. Set up proper project structure in Unreal Engine

## Scripts and Tools

### Python Script for Data Processing

Created separate processing scripts:
- `Scripts/process_swisstopo_data.py` - Main processing script
- `Scripts/convert_heightmap.py` - Format conversion utilities
- `Scripts/validate_data.py` - Data validation utilities

## Next Steps

1. Test with sample DHM25/200m data to validate workflow
2. Document exact Unreal Engine import settings
3. Create batch processing pipeline
4. Develop scripts for automated data updates
5. Create import runbook for team reference

## References

- Swisstopo Official Geodata Portal: https://shop.swisstopo.admin.ch/en/free-geodata
- Swisstopo Height Models: https://www.swisstopo.admin.ch/en/height-models
- Unreal Engine Landscape Documentation: https://docs.unrealengine.com/BuildingWorlds/Landscape/