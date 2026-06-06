# Track Editor Example Setup

This document describes how to set up a simple example using the track editor components.

## Overview

This example demonstrates how to use the track editor components to create a basic railway setup with a track and a station.

## Setup Steps

1. **Create a new level** in the Unreal Engine editor

2. **Place a Track Spline Actor**:
   - Right-click in the level viewport
   - Select "Track Spline Actor" from the Swisstrain Rail category
   - Place it in the level

3. **Edit the spline points**:
   - Select the Track Spline Actor
   - In the Details panel, find the Track Spline component
   - Click the "Edit Spline" button in the component toolbar
   - Add and move spline points to create a track route

4. **Adjust track settings**:
   - In the Details panel, adjust the MaxGradeDegrees property to control the maximum slope
   - Adjust the TerrainFollowOffset to control how high the track floats above the terrain

5. **Analyze the track**:
   - With the Track Spline Actor selected, click the "Recalculate With Grade Limits" button
   - Click the "Analyze Construction Features" button to identify where bridges, tunnels, cuts, or embankments are needed

6. **Place a Station**:
   - Right-click in the level viewport
   - Select "Station Actor" from the Swisstrain Rail category
   - Place it near one of the spline points

7. **Attach the Station to the Track**:
   - Select the Station Actor
   - In the Details panel, find the Station Anchor component
   - Click the "Snap To Track Spline" button to attach the station to the nearest spline point

8. **Configure the Station Type**:
   - In the Details panel, set the Station Type property to MainStation, HaltPoint, or Junction

## Expected Results

After following these steps, you should have:
- A track spline with multiple points
- The track adjusted to respect grade limits
- Construction features identified along the track
- A station attached to the track at a spline point
- The station configured with an appropriate type

## Troubleshooting

If you encounter issues:

1. **Station won't snap to track**:
   - Ensure the Track Spline Actor and Station Actor are in the same level
   - Check that the spline has valid points
   - Make sure you're using the "Snap To Track Spline" button on the Station Anchor component

2. **Track analysis shows no construction features**:
   - Ensure you have significant elevation changes along your spline
   - Check that the BridgeTunnelThreshold is set appropriately
   - Verify that terrain data is available in your level

3. **Editor tools not visible**:
   - Ensure the SwisstrainRail module is properly compiled and loaded
   - Check that you're in the correct editor mode
   - Verify that the plugin is enabled in the project settings