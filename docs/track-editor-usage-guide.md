# Track and Station Editor Tooling - Usage Guide

This guide explains how to use the editor tooling implemented for Swisstrain's track and station authoring system.

## Overview

The track editor tooling provides a comprehensive set of tools for creating railway tracks and stations within the Unreal Engine editor. The system is designed to be intuitive and visually appealing while providing helpful feedback during the creation process.

## Core Components

### 1. Track Spline System

The track spline system is the foundation for creating railway routes in the editor.

**Key Features:**
- Enhanced spline component specifically designed for railway tracks
- Grade limiting to prevent unrealistic track gradients
- Terrain following with configurable height offsets
- Automatic construction feature detection (bridges, tunnels, cuts, embankments)

**Usage:**
1. Place a Track Spline Actor in your level
2. Edit spline points in the editor viewport
3. Use the "Recalculate With Grade Limits" function to ensure realistic gradients
4. Run "Analyze Construction Features" to identify where bridges, tunnels, cuts, or embankments are needed

### 2. Station Placement System

The station system provides tools for placing stations and halt points along tracks.

**Key Features:**
- Station actors with anchor components for attaching to tracks
- Automatic snapping to track spline points
- Configurable station types (main station, halt point, junction)
- Visual indicators for passenger access points

**Usage:**
1. Place a Station Actor in your level
2. Use the Station Anchor Component to snap the station to a track spline
3. Configure the station type as needed (main station, halt point, junction)

### 3. Terrain Analysis and Construction Helpers

The terrain analysis system helps identify where construction features are needed and provides visual feedback.

**Key Features:**
- Automatic detection of elevation differences requiring construction features
- Visual feedback for bridge, tunnel, cut, and embankment decisions
- Terrain modification preview during track placement

**Usage:**
1. Run terrain analysis along your track spline
2. Review the ConstructionFeatures array to see where construction is needed
3. Use construction helpers to visualize proposed features in the editor

### 4. Editor Mode and Tools

The custom editor mode and tools provide an integrated workflow for railway construction.

**Key Features:**
- Dedicated editor mode for railway construction
- Interactive track placement tool with snapping and alignment assistance
- Station placement tool with automatic orientation
- Real-time feedback for construction decisions

**Usage:**
1. Activate the Track Editor Mode from the editor modes panel
2. Use the Track Placement Tool to create and modify track splines
3. Use the Station Placement Tool to add stations along tracks

## Asset Organization

The system uses a structured asset organization:

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

## Visual Feedback System

The editor provides immediate visual feedback during track placement:

- Green highlight for valid placement positions
- Red highlight for invalid placements (exceeding max gradient, etc.)
- Blue visualization for automatic bridge/tunnel decisions
- Brown visualization for embankment/cut requirements
- Temporary preview geometry showing proposed construction

## Best Practices

1. **Start Simple:** Begin with basic track layouts before adding complex terrain features
2. **Use Grade Limits:** Always run "Recalculate With Grade Limits" after adjusting spline points
3. **Analyze Construction:** Regularly analyze construction features to plan terrain modifications
4. **Preview Changes:** Use construction helpers to preview terrain modifications before finalizing
5. **Organize Assets:** Keep assets organized in the Content/Rail directory structure