# Track Editor Assets - Creation Guide

This guide describes the assets that need to be created for Swisstrain's track editor tooling to function properly.

## Overview

The track editor tooling requires several types of assets to provide a complete user experience:
1. Track visualization materials and meshes
2. Station assets for different station types
3. Construction feature visualization assets
4. Editor icons and UI elements

## Asset Directory Structure

All track-related assets should be organized in the following directory structure:

```
Content/Rail/
├── Tracks/
│   ├── Materials/
│   ├── Meshes/
│   └── Textures/
├── Stations/
│   ├── Materials/
│   ├── Meshes/
│   └── Textures/
├── Construction/
│   ├── Materials/
│   ├── Meshes/
│   └── Textures/
└── Icons/
    ├── Editor/
    └── UI/
```

## Track Assets

### Track Visualization Materials

Create materials for visualizing tracks in the editor:

1. **TrackSplineMaterial** - A material for visualizing the spline path
   - Should use a bright, visible color (e.g., yellow or orange)
   - Should be semi-transparent for better visibility
   - Should support different colors for valid/invalid placements

2. **TrackSegmentMaterial** - A material for visualizing track segments
   - Should represent railway tracks (rails, sleepers, ballast)
   - Should support different states (normal, selected, highlighted)

### Track Meshes

Create placeholder meshes for track visualization:

1. **TrackSplineMesh** - A simple mesh for visualizing the spline path
   - Should be a thin cylinder or ribbon following the spline
   - Should be optimized for performance as many instances will be used

2. **TrackSegmentMesh** - A mesh representing a section of railway track
   - Should include rails, sleepers, and ballast
   - Should support tiling for continuous track sections

## Station Assets

### Station Materials

Create materials for different station types:

1. **MainStationMaterial** - Material for main stations
   - Should be visually distinct (e.g., larger buildings, more details)
   - Should support different color schemes

2. **HaltPointMaterial** - Material for halt points
   - Should be simpler than main stations
   - Should still be clearly visible in the editor

3. **JunctionMaterial** - Material for junction stations
   - Should indicate multiple track connections
   - Should have a distinct visual style

### Station Meshes

Create placeholder meshes for different station types:

1. **MainStationMesh** - A mesh representing a main station building
   - Should include a platform and basic building structure
   - Should support attachment points for trains

2. **HaltPointMesh** - A mesh representing a simple halt point
   - Should be minimal (e.g., just a platform and small shelter)
   - Should be clearly distinguishable from main stations

3. **JunctionMesh** - A mesh representing a junction point
   - Should indicate track splitting/merging
   - Should include appropriate platform arrangements

## Construction Feature Assets

### Construction Materials

Create materials for visualizing construction features:

1. **BridgeMaterial** - Material for bridge visualization
   - Should represent bridge structures
   - Should be clearly visible against terrain

2. **TunnelMaterial** - Material for tunnel visualization
   - Should represent tunnel entrances
   - Should be distinct from other construction features

3. **CutMaterial** - Material for cut visualization
   - Should represent terrain excavation
   - Should use appropriate colors (e.g., brown/gray)

4. **EmbankmentMaterial** - Material for embankment visualization
   - Should represent raised terrain
   - Should use appropriate colors (e.g., brown/earth tones)

### Construction Meshes

Create placeholder meshes for construction features:

1. **BridgeMesh** - A mesh representing bridge structures
   - Should support different lengths and heights
   - Should integrate with track visualization

2. **TunnelMesh** - A mesh representing tunnel entrances
   - Should be optimized for visibility at ground level
   - Should indicate tunnel direction

3. **CutMesh** - A mesh representing terrain cuts
   - Should visualize excavated areas
   - Should integrate with landscape

4. **EmbankmentMesh** - A mesh representing raised track sections
   - Should visualize raised terrain
   - Should support varying heights

## Editor Icons

Create icons for use in the editor UI:

### Mode and Tool Icons

1. **TrackEditorModeIcon** - Icon for the track editor mode
2. **TrackPlacementToolIcon** - Icon for the track placement tool
3. **StationPlacementToolIcon** - Icon for the station placement tool

### Component Icons

1. **TrackSplineComponentIcon** - Icon for the track spline component
2. **StationAnchorComponentIcon** - Icon for the station anchor component
3. **RailTerrainAnalyzerIcon** - Icon for the terrain analyzer component
4. **RailConstructionHelperIcon** - Icon for the construction helper component

## UI Assets

Create assets for use in editor UI elements:

1. **TrackEditorStyles** - Style definitions for track editor UI
2. **ConstructionFeatureIcons** - Icons for different construction features
3. **StationTypeIcons** - Icons for different station types

## Asset Creation Workflow

When creating assets for the track editor:

1. **Start with Placeholders** - Create simple placeholder assets first to establish the workflow
2. **Test in Editor** - Import assets into the editor and test with the track editor tools
3. **Iterate on Design** - Refine assets based on how they appear and function in the editor
4. **Optimize for Performance** - Ensure assets are optimized for real-time editor performance
5. **Document Asset Usage** - Update documentation to reflect how assets should be used

## Asset Naming Conventions

Use consistent naming conventions for all assets:

- **Prefixes:** Use prefixes to indicate asset type (e.g., M_ for materials, SM_ for static meshes, T_ for textures)
- **Descriptive Names:** Use descriptive names that clearly indicate the asset's purpose
- **Consistent Casing:** Use PascalCase for asset names
- **Versioning:** Include version numbers when appropriate (e.g., SM_TrackSegment_v01)

## Asset Import Settings

When importing assets into Unreal:

1. **Textures:** Set appropriate compression settings based on usage
2. **Meshes:** Enable LOD generation for complex meshes
3. **Materials:** Ensure materials are set up for the Material Quality Level system
4. **Collision:** Set up appropriate collision geometry for interactive assets

## Future Asset Development

As the project evolves, plan for:

1. **Higher Quality Assets:** Replace placeholder assets with higher quality versions
2. **Dynamic Materials:** Create materials that respond to environmental conditions
3. **Animated Elements:** Add animation to assets like moving trains or waving vegetation
4. **Modular Systems:** Develop modular asset systems for easy customization