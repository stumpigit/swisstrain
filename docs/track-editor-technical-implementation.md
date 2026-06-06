# Track and Station Editor Tooling - Technical Implementation

This document provides technical details about the implementation of Swisstrain's track and station editor tooling.

## Module Structure

The implementation is organized within the SwisstrainRail module with the following structure:

```
Source/SwisstrainRail/
├── SwisstrainRail.Build.cs
├── Public/
│   ├── SwisstrainRail.h
│   ├── Track/
│   │   ├── TrackSplineComponent.h
│   │   └── TrackSplineActor.h
│   ├── Station/
│   │   ├── StationActor.h
│   │   └── StationAnchorComponent.h
│   └── Terrain/
│       ├── RailTerrainAnalyzer.h
│       └── RailConstructionHelper.h
└── Private/
    ├── SwisstrainRail.cpp
    ├── Track/
    │   ├── TrackSplineComponent.cpp
    │   └── TrackSplineActor.cpp
    ├── Station/
    │   ├── StationActor.cpp
    │   └── StationAnchorComponent.cpp
    └── Terrain/
        ├── RailTerrainAnalyzer.cpp
        └── RailConstructionHelper.cpp

Source/SwisstrainRail/Editor/
├── Public/
│   ├── TrackEditorMode.h
│   ├── TrackPlacementTool.h
│   └── StationPlacementTool.h
└── Private/
    ├── TrackEditorMode.cpp
    ├── TrackPlacementTool.cpp
    └── StationPlacementTool.cpp
```

## Core Component Implementations

### UTrackSplineComponent

The `UTrackSplineComponent` extends Unreal's `USplineComponent` with railway-specific functionality:

**Key Properties:**
- `MaxGradeDegrees`: Maximum allowed grade (slope) for the railway track
- `TerrainFollowOffset`: Height offset from terrain surface when following landscape
- `BridgeTunnelThreshold`: Distance threshold for automatic bridge/tunnel decisions
- `ConstructionFeatures`: Array of construction features identified along the track

**Key Functions:**
- `RecalculateWithGradeLimits()`: Recalculates spline points to respect maximum grade limits
- `AnalyzeConstructionFeatures()`: Analyzes terrain along spline and identifies construction features
- `AdjustPointForGradeLimit()`: Helper function to adjust spline point to maintain grade limits
- `GetTerrainHeightAtSplinePoint()`: Helper function to calculate terrain height at spline point

### ATrackSplineActor

The `ATrackSplineActor` is a container for the track spline component:

**Key Properties:**
- `TrackSpline`: The spline component that defines the track route
- `TrackVisualMaterial`: Material to use for visualizing the track route in the editor

### UStationAnchorComponent

The `UStationAnchorComponent` provides functionality for attaching stations to track splines:

**Key Properties:**
- `StationType`: The type of station (main station, halt point, junction)

**Key Functions:**
- `SnapToTrackSpline()`: Snaps the station to a track spline point with automatic orientation
- `SetStationType()`: Updates the station type and visuals

### AStationActor

The `AStationActor` represents a station or halt point in the level:

**Key Properties:**
- `StationAnchor`: The anchor component for attaching to tracks

### URailTerrainAnalyzer

The `URailTerrainAnalyzer` analyzes terrain to determine where construction features are needed:

**Key Properties:**
- `AnalysisResolution`: Distance between analysis points along the spline

**Key Functions:**
- `AnalyzeTerrainAlongSpline()`: Analyzes terrain along a spline to determine elevation changes
- `GetTerrainAnalysisAtPoint()`: Returns terrain analysis results at a specific point

### URailConstructionHelper

The `URailConstructionHelper` provides visual feedback for construction decisions:

**Key Functions:**
- `VisualizeConstructionFeature()`: Visualizes a construction feature in the editor
- `PreviewTerrainModification()`: Previews a terrain modification

## Editor Integration

### FTrackEditorMode

The `FTrackEditorMode` is a custom editor mode for railway construction:

**Key Features:**
- Integration with Unreal's editor mode system
- Support for custom editor tools

### FTrackPlacementTool

The `FTrackPlacementTool` is an interactive tool for placing track segments:

**Key Features:**
- Spline point editing in the editor viewport
- Snapping and alignment assistance

### FStationPlacementTool

The `FStationPlacementTool` is an interactive tool for placing stations:

**Key Features:**
- Automatic snapping to track splines
- Orientation assistance

## Build Configuration

The module's build configuration in `SwisstrainRail.Build.cs` includes dependencies on:

**Public Dependencies:**
- Core
- CoreUObject
- Engine
- Landscape
- Spline
- RenderCore
- RHI

**Private Dependencies:**
- CoreUObject
- Engine
- Slate
- SlateCore
- UnrealEd
- Landscape
- Spline
- RenderCore
- RHI

**Editor-Specific Dependencies:**
- EditorFramework
- EditorStyle
- UnrealEd
- LevelEditor
- InteractiveToolsFramework
- ToolMenus

## Remote Build Considerations

The implementation follows the remote build architecture where:
1. All editor-specific functionality is properly isolated
2. The module can be compiled without requiring Unreal Engine installation on the build host
3. Asset organization follows Unreal's conventions for easy transfer to the Windows authoring host

## Future Extensibility

The implementation is designed to be extensible:
1. Modular structure allows for easy addition of new features
2. Clear separation between core functionality and editor integration
3. Well-defined interfaces for terrain analysis and construction helpers
4. Scalable asset organization system