#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "TrainActor.generated.h"

class UTrackSplineComponent;
class AStationActor;

/**
 * Actor representing a train that moves along railway tracks.
 * Provides simple, satisfying movement with station stops and basic collision avoidance.
 */
UCLASS()
class SWISSTRAINRAIL_API ATrainActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ATrainActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * The spline component this train follows.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train Movement")
	UTrackSplineComponent* TrackSpline;

	/**
	 * Current distance along the spline where the train is positioned.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Train Movement")
	float DistanceAlongSpline;

	/**
	 * Current speed of the train in cm/s.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Train Movement")
	float CurrentSpeed;

	/**
	 * Maximum speed of the train in cm/s.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train Movement")
	float MaxSpeed;

	/**
	 * Acceleration rate in cm/s².
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train Movement")
	float Acceleration;

	/**
	 * Deceleration rate in cm/s².
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train Movement")
	float Deceleration;

	/**
	 * Time to wait at each station in seconds.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train Movement")
	float StationStopTime;

	/**
	 * List of stations this train will stop at.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train Movement")
	TArray<AStationActor*> ScheduledStations;

	/**
	 * Enable or disable basic collision avoidance with other trains.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train Movement")
	bool bEnableCollisionAvoidance;

private:
	// Current state of the train
	enum class ETrainState
	{
		Moving,
		ApproachingStation,
		StoppedAtStation,
		WaitingForClearPath
	};

	ETrainState CurrentState;

	// Index of the next station to stop at
	int32 NextStationIndex;

	// Timer for station stops
	float StationStopTimer;

	// Distance at which to start slowing down for a station
	float StationApproachDistance;

	// Reservation system to avoid collisions
	bool bHasReservation;

	// Update train position based on current speed and direction
	void UpdatePosition(float DeltaTime);

	// Check for stations ahead and handle stopping
	void HandleStationApproach(float DeltaTime);

	// Basic reservation system to prevent collisions
	bool RequestTrackReservation();
	void ReleaseTrackReservation();

	// Calculate distance to the next station
	float GetDistanceToNextStation() const;

	// Get the spline distance of the next station
	float GetNextStationSplineDistance() const;
};