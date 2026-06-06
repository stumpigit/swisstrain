# Swisstrain Terrain Import and Configuration Runbook

## Overview

This document provides a step-by-step guide for importing swisstopo terrain data into Unreal Engine 5.5 and configuring the landscape for the Swisstrain project.

## Prerequisites

Before starting, ensure you have:

1. Unreal Engine 5.5 installed
2. Swisstopo DHM data processed and available in the correct format
3. Basic understanding of Unreal Engine Landscape system
4. This project's Unreal Engine project open

## Swisstopo Data Preparation

### 1. Process Raw Swisstopo Data

Before importing into Unreal Engine, you must process the raw swisstopo data:

1. Download swisstopo DHM data for the bounding box:
   - Top-left: 2673957.58, 1216900.00 (EPSG:2056)
   - Bottom-right: 2689486.72, 1204462.45 (EPSG:2056)

2. Use the processing script to convert the data:
   ```
   python Scripts/process_swisstopo_data.py input.asc Content/Landscape/Heightmaps/ --width 2049 --height 2049
   ```

3. Validate the processed data:
   ```
   python Scripts/validate_swisstopo_data.py Content/Landscape/Heightmaps/processed_heightmap.raw --type raw --size 2049x2049
   ```

## Unreal Engine Import Process

### 1. Create New Landscape

1. Open the Swisstrain Unreal Engine project
2. In the Content Browser, navigate to Content/Landscape/
3. From the Modes panel, select the Landscape mode
4. Select "Create" from the Landscape tool
5. Choose "Import from File" under "Choose Your Method"

### 2. Configure Import Settings

1. Set Import Type to "Heightfield"
2. Click "Browse..." and select your processed heightmap RAW file
3. Set Import Resolution to match your processed data (e.g., 2049x2049)
4. Configure the following settings:
   - **Component Size**: 63 (adjust based on your needs)
   - **Subsection Size**: 64
   - **Number of Mipmap Levels**: 7
   - **Data Access Precision**: 8-bit (or 16-bit if you processed with high precision)

### 3. Configure Landscape Settings

#### Scale Settings

Based on our target area dimensions:
- Width: 15529.14 meters
- Height: 12437.55 meters

Settings to configure in the Landscape tool:
- **Location X**: 0 (or appropriate world position)
- **Location Y**: 0 (or appropriate world position)
- **Scale X**: 7.6 (approximately 15529.14m / 2049 pixels)
- **Scale Y**: 6.1 (approximately 12437.55m / 2049 pixels)
- **Scale Z**: 1.0 (or adjust for vertical exaggeration)

#### Vertical Scaling

- **Minimum Z**: Adjust to match the minimum elevation in your data
- **Maximum Z**: Adjust to match the maximum elevation in your data
- **Z Scale**: 1.0 (or adjust for artistic effect)

### 4. Import and Generate

1. Click "Import" to generate the landscape
2. Wait for the import process to complete
3. Verify the landscape appears correctly in the viewport

## Post-Import Configuration

### 1. Material Setup

1. Create a new Landscape Material in Content/Landscape/Materials/
2. Assign appropriate layers for:
   - Rock/Felsen
   - Grass/Wiese
   - Forest/Wald
   - Dirt/Schotter
3. Configure material blend weights based on slope and elevation
4. Apply the material to the landscape

### 2. Water System

1. Create or import water materials
2. Identify water bodies in the heightmap (low-lying areas)
3. Use Landscape Sculpting tools to adjust water areas
4. Add Water bodies using the Water system

### 3. Vegetation/Foliage

1. Set up Foliage Types in Content/Landscape/Foliage/
2. Configure Landscape Grass Types for:
   - Alpine grasses
   - Shrubs
   - Trees appropriate to Swiss alpine regions
3. Paint foliage using the Foliage painting tools

### 4. Lighting and Atmosphere

1. Add a Sky Light component
2. Configure directional light for appropriate time of day
3. Add Exponential Height Fog for atmospheric perspective
4. Adjust Post Process Volume settings for mood
5. Add Sky Atmosphere component for realistic sky

## Testing and Validation

### 1. Visual Quality Check

1. Examine the terrain from multiple camera angles
2. Check for any obvious artifacts or seams
3. Verify elevation data matches expected Swiss topography
4. Confirm water bodies are placed appropriately

### 2. Performance Testing

1. Check frame rate in different areas of the landscape
2. Monitor memory usage
3. Identify any performance bottlenecks
4. Adjust landscape settings if needed

### 3. Navigation Testing

1. Test character navigation on the terrain
2. Verify walkable slopes
3. Check collision and physics behavior

## Common Issues and Solutions

### 1. Import Scaling Issues

**Problem**: Terrain appears too large or small
**Solution**: 
- Recalculate scale values
- Verify heightmap dimensions match import settings
- Adjust Landscape scale settings post-import

### 2. Height Range Problems

**Problem**: Terrain appears flat or exaggerated
**Solution**:
- Check minimum/maximum Z settings
- Verify vertical scale factor
- Reprocess heightmap with correct elevation range

### 3. Seams in Tiled Imports

**Problem**: Visible seams between landscape tiles
**Solution**:
- Ensure proper overlap in source data
- Use matching Component Size settings
- Adjust Landscape sector settings for seamless blending

## Export and Version Control

### 1. File Organization

Maintain the following structure:
```
Content/
├── Landscape/
│   ├── Heightmaps/
│   │   ├── Processed_RAW/
│   │   ├── Original_ASC/
│   │   └── Info_Files/
│   ├── Materials/
│   ├── Textures/
│   ├── Water/
│   └── Foliage/
└── Maps/
```

### 2. Git LFS Configuration

Ensure Git LFS is tracking large files:
```
git lfs track "*.raw"
git lfs track "*.uasset"
git lfs track "*.umap"
```

### 3. Documentation Updates

Update this runbook with any changes to the process:
- New tools or scripts
- Different import settings that work better
- Additional quality checks
- Performance optimization techniques

## Next Steps After Basic Import

1. Artistic enhancement and cleanup
2. Integration with track/editor systems
3. Performance optimization
4. Documentation and handoff for team members

This runbook should be updated as we discover new best practices or encounter issues during development.