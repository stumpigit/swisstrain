#include "Simulation/TrainActor.h"
#include "Track/TrackSplineComponent.h"
#include "Station/StationActor.h"
#include "Station/StationAnchorComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
ATrainActor::ATrainActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a root component for the train
	USceneComponent* TrainRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TrainRoot"));
	RootComponent = TrainRoot;

	// Initialize default values
	DistanceAlongSpline = 0.0f;
	CurrentSpeed = 0.0f;
	MaxSpeed = 1000.0f; // 10 m/s
	Acceleration = 200.0f; // 2 m/s²
	Deceleration = 400.0f; // 4 m/s²
	StationStopTime = 10.0f; // Stop for 10 seconds at each station
	bEnableCollisionAvoidance = true;

	CurrentState = ETrainState::Moving;
	NextStationIndex = 0;
	StationStopTimer = 0.0f;
	StationApproachDistance = 2000.0f; // Start slowing down 20 meters before station
	bHasReservation = false;
}

// Called when the game starts or when spawned
void ATrainActor::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the train
	if (TrackSpline)
	{
		// Position the train at the start of the spline
		FTransform StartTransform = TrackSpline->GetTransformAtSplinePoint(0, ESplineCoordinateSpace::World);
		SetActorTransform(StartTransform);
	}
}

// Called every frame
void ATrainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TrackSpline)
	{
		return;
	}

	// Handle different train states
	switch (CurrentState)
	{
	case ETrainState::Moving:
	case ETrainState::ApproachingStation:
		UpdatePosition(DeltaTime);
		HandleStationApproach(DeltaTime);
		break;

	case ETrainState::StoppedAtStation:
		StationStopTimer += DeltaTime;
		if (StationStopTimer >= StationStopTime)
		{
			StationStopTimer = 0.0f;
			CurrentState = ETrainState::Moving;
			CurrentSpeed = 0.0f;
		}
		break;

	case ETrainState::WaitingForClearPath:
		// Check if the path is clear now
		if (RequestTrackReservation())
		{
			CurrentState = ETrainState::Moving;
		}
		break;
	}

	// Update train position on the spline
	if (TrackSpline)
	{
		FVector NewLocation = TrackSpline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		FRotator NewRotation = TrackSpline->GetRotationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}

void ATrainActor::UpdatePosition(float DeltaTime)
{
	// Accelerate towards max speed
	if (CurrentSpeed < MaxSpeed)
	{
		CurrentSpeed += Acceleration * DeltaTime;
		if (CurrentSpeed > MaxSpeed)
		{
			CurrentSpeed = MaxSpeed;
		}
	}

	// Update distance along spline
	DistanceAlongSpline += CurrentSpeed * DeltaTime;

	// Handle spline looping - if we reach the end, loop back to the beginning
	if (DistanceAlongSpline > TrackSpline->GetSplineLength())
	{
		DistanceAlongSpline = 0.0f;
		NextStationIndex = 0; // Reset station index
	}
}

void ATrainActor::HandleStationApproach(float DeltaTime)
{
	// Check if we have scheduled stations
	if (ScheduledStations.Num() == 0 || NextStationIndex >= ScheduledStations.Num())
	{
		return;
	}

	// Get distance to next station
	float DistanceToStation = GetDistanceToNextStation();

	// If we're approaching a station
	if (DistanceToStation <= StationApproachDistance && CurrentState != ETrainState::ApproachingStation)
	{
		CurrentState = ETrainState::ApproachingStation;
	}

	// If we're approaching a station, start slowing down
	if (CurrentState == ETrainState::ApproachingStation)
	{
		// Calculate required deceleration to stop at the station
		// Using v² = u² + 2as where v=0, u=CurrentSpeed, s=DistanceToStation
		// So a = -u²/(2s)
		if (DistanceToStation > 0.0f)
		{
			float RequiredDecel = (CurrentSpeed * CurrentSpeed) / (2.0f * DistanceToStation);
			
			// Apply the required deceleration, but don't exceed our maximum deceleration
			float ActualDecel = FMath::Min(RequiredDecel, Deceleration);
			CurrentSpeed -= ActualDecel * DeltaTime;
			
			// Ensure we don't go backwards
			if (CurrentSpeed < 0.0f)
			{
				CurrentSpeed = 0.0f;
			}
		}

		// If we've reached the station
		if (DistanceToStation <= 100.0f) // Within 1 meter
		{
			CurrentSpeed = 0.0f;
			CurrentState = ETrainState::StoppedAtStation;
			StationStopTimer = 0.0f;
			NextStationIndex++; // Move to next station

			// Release reservation when stopped
			if (bHasReservation)
			{
				ReleaseTrackReservation();
			}
		}
	}
}

bool ATrainActor::RequestTrackReservation()
{
	// Simple reservation system - in a more complex implementation,
	// this would check with a central traffic controller
	if (bEnableCollisionAvoidance)
	{
		// For now, we'll just assume we get the reservation
		// In a real implementation, this would check with other trains
		bHasReservation = true;
		return true;
	}
	
	bHasReservation = true;
	return true;
}

void ATrainActor::ReleaseTrackReservation()
{
	bHasReservation = false;
}

float ATrainActor::GetDistanceToNextStation() const
{
	if (ScheduledStations.Num() == 0 || NextStationIndex >= ScheduledStations.Num())
	{
		return FLT_MAX; // No more stations
	}

	return GetNextStationSplineDistance() - DistanceAlongSpline;
}

float ATrainActor::GetNextStationSplineDistance() const
{
	if (ScheduledStations.Num() == 0 || NextStationIndex >= ScheduledStations.Num())
	{
		return 0.0f;
	}

	AStationActor* NextStation = ScheduledStations[NextStationIndex];
	if (NextStation && NextStation->StationAnchor)
	{
		return NextStation->StationAnchor->DistanceAlongSpline;
	}

	return 0.0f;
}