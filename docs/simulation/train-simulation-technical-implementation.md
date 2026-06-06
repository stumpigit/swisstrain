# Train Simulation System - Technical Implementation

This document provides technical details about the implementation of the train simulation system for Swisstrain.

## Module Structure

The simulation system is organized within the SwisstrainRail module with the following structure:

```
Source/SwisstrainRail/
├── Public/
│   ├── Simulation/
│   │   ├── TrainActor.h
│   │   ├── TrainMovementComponent.h
│   │   └── TrafficControllerActor.h
└── Private/
    ├── Simulation/
        ├── TrainActor.cpp
        ├── TrainMovementComponent.cpp
        └── TrafficControllerActor.cpp
```

## Core Component Implementations

### ATrainActor

The `ATrainActor` is an actor that represents a train moving along railway tracks. It provides simple, satisfying movement with station stops and basic collision avoidance.

**Key Properties:**
- `TrackSpline`: The spline component this train follows
- `DistanceAlongSpline`: Current distance along the spline where the train is positioned
- `CurrentSpeed`: Current speed of the train in cm/s
- `MaxSpeed`: Maximum speed of the train in cm/s
- `Acceleration`: Acceleration rate in cm/s²
- `Deceleration`: Deceleration rate in cm/s²
- `StationStopTime`: Time to wait at each station in seconds
- `ScheduledStations`: List of stations this train will stop at
- `bEnableCollisionAvoidance`: Enable or disable basic collision avoidance with other trains

**Key Functions:**
- `UpdatePosition()`: Update train position based on current speed and direction
- `HandleStationApproach()`: Check for stations ahead and handle stopping
- `RequestTrackReservation()`: Basic reservation system to prevent collisions
- `ReleaseTrackReservation()`: Release track reservation
- `GetDistanceToNextStation()`: Calculate distance to the next station
- `GetNextStationSplineDistance()`: Get the spline distance of the next station

### UTrainMovementComponent

The `UTrainMovementComponent` is a component that can be attached to any actor to give it train movement capabilities. It handles spline following, station stops, and basic collision avoidance.

**Key Properties:**
- `TrackSpline`: The spline component this train follows
- `DistanceAlongSpline`: Current distance along the spline where the train is positioned
- `CurrentSpeed`: Current speed of the train in cm/s
- `MaxSpeed`: Maximum speed of the train in cm/s
- `Acceleration`: Acceleration rate in cm/s²
- `Deceleration`: Deceleration rate in cm/s²
- `StationStopTime`: Time to wait at each station in seconds
- `ScheduledStations`: List of stations this train will stop at
- `bEnableCollisionAvoidance`: Enable or disable basic collision avoidance with other trains

**Key Functions:**
- `UpdateTrainPosition()`: Update the owner actor's position based on the train movement
- `UpdatePosition()`: Update train position based on current speed and direction
- `HandleStationApproach()`: Check for stations ahead and handle stopping
- `RequestTrackReservation()`: Basic reservation system to prevent collisions
- `ReleaseTrackReservation()`: Release track reservation
- `GetDistanceToNextStation()`: Calculate distance to the next station
- `GetNextStationSplineDistance()`: Get the spline distance of the next station

### ATrafficControllerActor

The `ATrafficControllerActor` is an actor that manages traffic control for trains to prevent collisions. It implements a simple reservation system for track segments.

**Key Properties:**
- `ReservationTimeout`: Time before an unused reservation expires (in seconds)

**Key Functions:**
- `RegisterTrain()`: Register a train with the traffic controller
- `UnregisterTrain()`: Unregister a train from the traffic controller
- `RegisterTrainMovement()`: Register a train movement component with the traffic controller
- `UnregisterTrainMovement()`: Unregister a train movement component from the traffic controller
- `RequestTrackReservation()`: Request reservation for a track segment
- `ReleaseTrackReservation()`: Release a track segment reservation
- `CleanupExpiredReservations()`: Check for and clean up expired reservations

## Features Implemented

### 1. Spline-Based Movement

Trains follow railway tracks using the existing `UTrackSplineComponent` system:
- Smooth movement along spline curves
- Automatic orientation to match track direction
- Support for looping tracks

### 2. Station Stopping

Trains automatically stop at scheduled stations:
- Configurable stop duration
- Smooth acceleration/deceleration
- Distance-based approach detection

### 3. Basic Collision Avoidance

Simple reservation system to prevent train collisions:
- Track segment reservation
- Automatic waiting when path is blocked
- Reservation timeout cleanup

### 4. Scenic Running

Movement designed for camera-friendly operation:
- Smooth acceleration and deceleration
- Predictable station stops
- Pleasant travel speeds

## Usage Examples

### Creating a Simple Train

```cpp
// In your level blueprint or C++ code
ATrainActor* Train = GetWorld()->SpawnActor<ATrainActor>(TrainActorClass, SpawnLocation, SpawnRotation);
Train->TrackSpline = YourTrackSplineComponent;
Train->ScheduledStations = YourStationArray;
Train->MaxSpeed = 1000.0f; // 10 m/s
Train->Acceleration = 200.0f; // 2 m/s²
Train->Deceleration = 400.0f; // 4 m/s²
```

### Using Train Movement Component

```cpp
// Attach to any actor to give it train movement capabilities
UTrainMovementComponent* TrainMovement = YourActor->FindComponentByClass<UTrainMovementComponent>();
if (TrainMovement)
{
    TrainMovement->TrackSpline = YourTrackSplineComponent;
    TrainMovement->ScheduledStations = YourStationArray;
}
```

### Setting Up Traffic Control

```cpp
// Create a traffic controller to manage multiple trains
ATrafficControllerActor* TrafficController = GetWorld()->SpawnActor<ATrafficControllerActor>();
TrafficController->RegisterTrain(YourTrainActor);
```

## Future Extensibility

The implementation is designed to be extensible:
1. Modular structure allows for easy addition of new features
2. Clear separation between movement logic and visual representation
3. Well-defined interfaces for traffic control integration
4. Blueprint-friendly properties and functions for easy customization