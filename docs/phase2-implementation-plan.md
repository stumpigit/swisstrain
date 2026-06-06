# Phase 2: Track and Station Editor Tooling - Implementation Plan

## Overview
This document outlines the approach for implementing editor-first track authoring tools for the Swisstrain Swiss landscape prototype. The implementation will focus on spline laying, station placement anchors, grade constraints, and automated handling of bridge/tunnel/cut/embankment decisions suitable for a pleasing sandbox workflow.

## Key Requirements from V1 Specification
Based on the V1 specification (lines 74-97):
1. Spline-based track route placement (`Spline-basierte Streckenanlage`)
2. Simple station/halt points or anchors (`einfache Stations-/Haltepunkte oder Anker`)
3. Height and route rules to avoid extreme chaos (`Höhen- und Verlaufsregeln, die extremes Chaos vermeiden`)
4. Visual or semi-automatic handling of embankments, cuts, bridges, and tunnels
5. Good visual feedback during placement and editing (`gutes visuelles Feedback beim Platzieren und Bearbeiten`)

## Implementation Approach

### 1. Unreal Engine Module Structure
The SwisstrainRail module will contain the track editing functionality:
- `Source/SwisstrainRail/` - Core track system implementation
- `Source/SwisstrainRail/Editor/` - Editor-specific functionality
- `Content/Rail/` - Asset organization for tracks and stations

### 2. Core Components to Implement

#### A. Track Spline System
- `UTrackSplineComponent` - Enhanced spline component for railway tracks
- `ATrackSplineActor` - Main actor for placing track splines in the environment
- Features:
  - Snapping to terrain with configurable height offset
  - Auto-grade management with max gradient constraints
  - Visual feedback for valid/invalid placement
  - Spline point editing in the editor viewport

#### B. Station Placement System
- `AStationActor` - Base actor for stations and halt points
- `UStationAnchorComponent` - Component for attaching stations to track splines
- Features:
  - Snap to track spline points with automatic orientation
  - Configurable station types (main station, halt point, junction)
  - Visual indicators for passenger access points

#### C. Terrain Interaction System
- `URailTerrainAnalyzer` - Analyzes terrain to determine embankment/cut/bridge/tunnel requirements
- `URailConstructionHelper` - Provides visual feedback for construction decisions
- Features:
  - Automatic detection of elevation differences requiring bridges/tunnels
  - Embankment/cut volume calculations for visual feedback
  - Terrain modification preview during track placement

#### D. Editor Mode and Tools
- `FTrackEditorMode` - Custom editor mode for railway construction
- `UTrackPlacementTool` - Interactive tool for placing track segments
- `UStationPlacementTool` - Interactive tool for placing stations
- Features:
  - Dedicated editor mode toggle
  - Snapping and alignment assistance
  - Real-time feedback for construction decisions

### 3. Implementation Steps

#### Step 1: Establish Module Structure
1. Create complete SwisstrainRail module with build configuration
2. Set up directory structure following Unreal Engine conventions
3. Create base classes for track and station systems

#### Step 2: Implement Spline-Based Track System
1. Create `UTrackSplineComponent` with railway-specific functionality
2. Implement `ATrackSplineActor` for editor placement
3. Add terrain following and height constraint logic
4. Create visual feedback system for valid/invalid placement

#### Step 3: Add Station Placement System
1. Create `AStationActor` base class with anchor functionality
2. Implement snapping to track splines
3. Add station type configuration options

#### Step 4: Implement Terrain Analysis and Construction Helpers
1. Create `URailTerrainAnalyzer` for automatic feature detection
2. Develop algorithms for bridge/tunnel/cut/embankment detection
3. Implement visual feedback for construction decisions
4. Add preview functionality for terrain modifications

#### Step 5: Create Editor Tools and Mode
1. Implement custom editor mode for railway construction
2. Create placement tools with snapping and alignment assistance
3. Add interactive editing capabilities
4. Implement undo/redo functionality for editor actions

#### Step 6: Testing and Documentation
1. Create example scenes demonstrating track and station placement
2. Document tool usage in editor workflow guide
3. Create configuration guide for adjusting track parameters

### 4. Visual Feedback Concepts
The system will provide immediate visual feedback during track placement:
- Green highlight for valid placement positions
- Red highlight for invalid placements (exceeding max gradient, etc.)
- Blue visualization for automatic bridge/tunnel decisions
- Brown visualization for embankment/cut requirements
- Temporary preview geometry showing proposed construction

### 5. Asset Organization Plan
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

### 6. Code Structure Plan
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

## Next Steps
This plan will be implemented incrementally with frequent commits to track progress. Each major component will be documented as it's completed to ensure the work is reviewable even without Unreal Engine installation.