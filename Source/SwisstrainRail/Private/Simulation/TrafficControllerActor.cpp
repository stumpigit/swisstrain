#include "Simulation/TrafficControllerActor.h"
#include "Simulation/TrainActor.h"
#include "Simulation/TrainMovementComponent.h"
#include "Track/TrackSplineComponent.h"

// Sets default values
ATrafficControllerActor::ATrafficControllerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReservationTimeout = 30.0f; // Reservations expire after 30 seconds if not renewed
}

// Called when the game starts or when spawned
void ATrafficControllerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrafficControllerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CleanupExpiredReservations(DeltaTime);
}

void ATrafficControllerActor::RegisterTrain(ATrainActor* Train)
{
	if (Train && !RegisteredTrains.Contains(Train))
	{
		RegisteredTrains.Add(Train);
	}
}

void ATrafficControllerActor::UnregisterTrain(ATrainActor* Train)
{
	if (Train)
	{
		RegisteredTrains.Remove(Train);
		
		// Release any reservations this train might have
		for (int32 i = TrackReservations.Num() - 1; i >= 0; --i)
		{
			if (TrackReservations[i].ReservedBy == Train)
			{
				TrackReservations.RemoveAt(i);
			}
		}
	}
}

void ATrafficControllerActor::RegisterTrainMovement(UTrainMovementComponent* TrainMovement)
{
	if (TrainMovement && !RegisteredTrainMovements.Contains(TrainMovement))
	{
		RegisteredTrainMovements.Add(TrainMovement);
	}
}

void ATrafficControllerActor::UnregisterTrainMovement(UTrainMovementComponent* TrainMovement)
{
	if (TrainMovement)
	{
		RegisteredTrainMovements.Remove(TrainMovement);
	}
}

bool ATrafficControllerActor::RequestTrackReservation(ATrainActor* Train, UTrackSplineComponent* TrackSpline, float StartDistance, float EndDistance)
{
	if (!Train || !TrackSpline)
	{
		return false;
	}

	// Check if this segment is already reserved by another train
	for (const FTrackReservation& Reservation : TrackReservations)
	{
		// Check if reservations overlap
		if (Reservation.TrackSpline == TrackSpline &&
			Reservation.ReservedBy != Train &&
			!(StartDistance > Reservation.EndDistance || EndDistance < Reservation.StartDistance))
		{
			// Overlapping reservation found
			return false;
		}
	}

	// No conflicting reservations, grant the request
	FTrackReservation NewReservation(Train, TrackSpline, StartDistance, EndDistance);
	TrackReservations.Add(NewReservation);
	return true;
}

void ATrafficControllerActor::ReleaseTrackReservation(ATrainActor* Train, UTrackSplineComponent* TrackSpline, float StartDistance, float EndDistance)
{
	if (!Train || !TrackSpline)
	{
		return;
	}

	// Find and remove the matching reservation
	for (int32 i = TrackReservations.Num() - 1; i >= 0; --i)
	{
		FTrackReservation& Reservation = TrackReservations[i];
		if (Reservation.ReservedBy == Train &&
			Reservation.TrackSpline == TrackSpline &&
			FMath::IsNearlyEqual(Reservation.StartDistance, StartDistance) &&
			FMath::IsNearlyEqual(Reservation.EndDistance, EndDistance))
		{
			TrackReservations.RemoveAt(i);
			return;
		}
	}
}

void ATrafficControllerActor::CleanupExpiredReservations(float DeltaTime)
{
	// Update reservation times and remove expired ones
	for (int32 i = TrackReservations.Num() - 1; i >= 0; --i)
	{
		TrackReservations[i].ReservationTime += DeltaTime;
		if (TrackReservations[i].ReservationTime > ReservationTimeout)
		{
			TrackReservations.RemoveAt(i);
		}
	}
}