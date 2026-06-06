# Swisstrain Train Simulation - Testing Guide

## Overview

This document describes how to test the train simulation system implemented in Phase 3.

## Prerequisites

1. Unreal Engine 5.5 installed on Windows (remote authoring host)
2. Swisstrain project transferred to Windows authoring host
3. Completed track network with stations from Phase 2

## Testing Steps

### 1. Open the Example Map

1. Launch Unreal Engine Editor on the Windows authoring host
2. Open the Swisstrain project
3. Load the example map: `Content/Maps/SwisstrainExample.umap`

### 2. Verify Track and Station Setup

1. Confirm that railway tracks have been authored using the Track Editor tools
2. Verify that stations are placed along the tracks and properly anchored
3. Check that track splines are continuous and valid

### 3. Place and Configure a Train Actor

1. Right-click in the level viewport
2. Select "Place Actor" > "Train Actor"
3. Place the train at the beginning of a track segment
4. In the Details panel, configure:
   - Set the "Track Spline" property to your track's spline component
   - Add stations to the "Scheduled Stations" array
   - Adjust movement parameters (Max Speed, Acceleration, etc.)

### 4. Add Visual Representation

1. With the Train Actor selected, add a Static Mesh Component
2. Assign an appropriate train model to the mesh
3. Position and scale the mesh to match the track

### 5. Test the Simulation

1. Press Play to start the simulation
2. Observe the train moving along the track
3. Verify that the train stops at each scheduled station
4. Check that acceleration and deceleration feel natural
5. Confirm that the train follows the track curvature correctly

### 6. Test Multiple Trains (Optional)

1. Place additional Train Actors on the same or intersecting tracks
2. Create a TrafficControllerActor if not already present
3. Register all trains with the traffic controller
4. Play the simulation and observe collision avoidance behavior

## Expected Results

- Trains should smoothly follow track splines
- Trains should stop at all scheduled stations for the configured duration
- Trains should accelerate and decelerate naturally
- Multiple trains should avoid collisions when using the traffic controller

## Troubleshooting

- If trains don't move, check that the Track Spline property is set correctly
- If trains don't stop at stations, verify the Scheduled Stations array
- If trains behave erratically, check the track spline for errors
- If collision avoidance fails, ensure all trains are registered with the same traffic controller

## Next Steps

After successful testing:
1. Package the simulation for deployment
2. Create additional train routes and schedules
3. Add visual and audio effects for enhanced realism
4. Implement more advanced features as needed