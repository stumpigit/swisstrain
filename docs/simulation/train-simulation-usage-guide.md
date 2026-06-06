# Train Simulation System - Usage Guide

This document provides instructions for using the train simulation system in Swisstrain.

## Overview

The train simulation system provides simple, satisfying train movement along authored railway tracks with station stops and basic collision avoidance. The system is designed to be easy to use while providing camera-friendly movement for scenic runs through the landscape.

## Components

The simulation system consists of three main components:

1. **Train Actor** - A complete actor that represents a moving train
2. **Train Movement Component** - A component that can be attached to any actor to give it train movement capabilities
3. **Traffic Controller Actor** - An actor that manages traffic control to prevent collisions between trains

## Setting Up a Basic Train

### 1. Create a Track with Stations

Before creating trains, ensure you have:
- A `TrackSplineActor` with a `TrackSplineComponent` representing your railway track
- `StationActor` instances placed along the track and anchored to the spline

### 2. Create a Train Actor

In the Unreal Editor:

1. Right-click in the level viewport
2. Select "Place Actor" > "Train Actor"
3. Place the train in your level

### 3. Configure Train Properties

In the Details panel for your Train Actor:

1. Set the `Track Spline` property to your track's `TrackSplineComponent`
2. Add your stations to the `Scheduled Stations` array
3. Adjust movement parameters as needed:
   - `Max Speed`: Maximum speed in cm/s (default: 1000 cm/s = 10 m/s)
   - `Acceleration`: Acceleration rate in cm/s² (default: 200 cm/s² = 2 m/s²)
   - `Deceleration`: Deceleration rate in cm/s² (default: 400 cm/s² = 4 m/s²)
   - `Station Stop Time`: Duration to stop at each station in seconds (default: 10 seconds)

### 4. Play the Simulation

Press Play to see your train move along the track, stopping at each scheduled station.

## Using the Train Movement Component

To add train movement to an existing actor:

1. Select your actor in the level
2. In the Details panel, click "Add Component"
3. Select "Train Movement Component"
4. Configure the component properties as described above

This approach is useful when you want to animate existing train mesh actors or create more complex train compositions.

## Setting Up Traffic Control

For scenarios with multiple trains, set up a traffic controller:

1. Place a `TrafficControllerActor` in your level
2. Register your trains with the controller:
   - In Blueprints: Call "Register Train" for each train
   - In C++: Call `TrafficController->RegisterTrain(YourTrainActor);`

The traffic controller will automatically manage reservations to prevent collisions.

## Configuration Options

### Movement Parameters

- **Max Speed**: Controls how fast the train can travel (in cm/s)
- **Acceleration**: How quickly the train speeds up (in cm/s²)
- **Deceleration**: How quickly the train slows down (in cm/s²)
- **Station Stop Time**: How long the train waits at each station (in seconds)

### Collision Avoidance

- **Enable Collision Avoidance**: Toggle basic collision prevention (default: enabled)
- **Reservation Timeout**: How long unused reservations last before expiring (default: 30 seconds)

### Visual Feedback

Trains automatically orient to match the track direction. You can add visual components like:
- Mesh components for train models
- Particle systems for effects
- Lights for nighttime operation

## Best Practices

### Performance

- Limit the number of active trains to maintain good performance
- Use simple meshes for train models during development
- Consider using Level of Detail (LOD) for complex train models

### Design

- Place stations at reasonable intervals along your tracks
- Adjust train speeds to match the scale and atmosphere of your scene
- Use multiple trains sparingly to avoid congestion

### Testing

- Test train movement with different track layouts
- Verify that trains stop correctly at all scheduled stations
- Check for collision issues when using multiple trains

## Troubleshooting

### Train Not Moving

- Check that the `Track Spline` property is set to a valid `TrackSplineComponent`
- Verify that the train is not stopped at a station (wait for it to depart)
- Ensure the simulation is running (press Play)

### Train Not Stopping at Stations

- Verify that stations are added to the `Scheduled Stations` array
- Check that stations are properly anchored to the track spline
- Ensure the station anchor's `Distance Along Spline` is correct

### Collision Issues

- Make sure all trains are registered with the traffic controller
- Check that the `Enable Collision Avoidance` property is set to true
- Verify that trains are using the same traffic controller instance

## Extending the System

The simulation system is designed to be extensible. Common extensions might include:

- Custom acceleration/deceleration profiles
- Advanced scheduling systems
- More sophisticated collision avoidance
- Sound and visual effects
- Passenger loading/unloading animations

For implementation details, see the [Technical Implementation Guide](train-simulation-technical-implementation.md).