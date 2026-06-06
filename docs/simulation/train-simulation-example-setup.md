# Train Simulation - Example Setup

This document provides step-by-step instructions for setting up a basic train simulation in Swisstrain.

## Prerequisites

Before setting up the train simulation, you should have:
- A level with terrain (from Phase 1)
- Authored railway tracks using the Track Editor (from Phase 2)
- Placed stations along your tracks

## Step 1: Verify Your Track Setup

1. Open your level in the Unreal Editor
2. Ensure you have a `TrackSplineActor` with a valid `TrackSplineComponent`
3. Verify that you have `StationActor` instances placed along your track
4. Check that stations are properly anchored to the track spline

## Step 2: Place a Train Actor

1. Right-click in the level viewport
2. Select "Place Actor" from the context menu
3. In the search box, type "Train Actor"
4. Select "TrainActor" from the results and place it in your level

## Step 3: Configure the Train

1. Select the Train Actor you just placed
2. In the Details panel, find the "Train Movement" category
3. Set the "Track Spline" property:
   - Click the dropdown next to the property
   - Select your track's `TrackSplineComponent` from the list
4. Configure the Scheduled Stations:
   - Expand the "Scheduled Stations" array property
   - Click the "+" button to add stations
   - For each station, select the appropriate `StationActor` from your level

## Step 4: Adjust Movement Parameters

In the Details panel, adjust the following parameters as desired:

1. **Max Speed**: Set the maximum speed for your train (default: 1000.0)
2. **Acceleration**: Set how quickly the train accelerates (default: 200.0)
3. **Deceleration**: Set how quickly the train decelerates (default: 400.0)
4. **Station Stop Time**: Set how long the train stops at each station in seconds (default: 10.0)

## Step 5: Add Visual Representation

The Train Actor doesn't include a visual mesh by default. To see your train:

1. With the Train Actor selected, click "Add Component" in the Details panel
2. Select "Static Mesh Component"
3. In the new component's properties:
   - Set the "Static Mesh" to a train model
   - Adjust the "Location" and "Rotation" to position the mesh correctly
   - Adjust the "Scale" if needed

## Step 6: Test the Simulation

1. Save your level
2. Press the Play button to start the simulation
3. Observe the train moving along the track and stopping at stations

## Example Configuration

Here's an example configuration for a scenic mountain route:

```
- Max Speed: 800.0 (8 m/s - slower for scenic mountain routes)
- Acceleration: 150.0 (1.5 m/s² - gentle acceleration)
- Deceleration: 300.0 (3 m/s² - smooth braking)
- Station Stop Time: 15.0 (15 seconds - longer stops for scenery)
```

## Multi-Train Setup

To set up multiple trains on the same track:

1. Place additional Train Actors as described above
2. Create a TrafficControllerActor:
   - Right-click in the level viewport
   - Select "Place Actor" > "TrafficControllerActor"
3. Register trains with the traffic controller:
   - Select the TrafficControllerActor
   - In the Details panel, find the "Registered Trains" array
   - Add your train actors to this array

## Troubleshooting

### Common Issues and Solutions

1. **Train spins wildly or moves incorrectly**
   - Check that the Track Spline property is set correctly
   - Verify that the track spline has valid control points

2. **Train doesn't stop at stations**
   - Verify that Scheduled Stations array contains your stations
   - Check that station anchors are properly configured

3. **Trains collide despite traffic control**
   - Ensure all trains are registered with the same TrafficControllerActor
   - Verify that Enable Collision Avoidance is set to true

4. **Train moves too fast/slow**
   - Adjust the Max Speed parameter
   - Modify Acceleration/Deceleration for different feel

## Next Steps

After setting up the basic simulation, consider:

1. Adding more detailed train models with multiple cars
2. Implementing day/night lighting for the trains
3. Adding sound effects for train movement and station stops
4. Creating multiple routes with different trains
5. Setting up a control panel to start/stop trains manually