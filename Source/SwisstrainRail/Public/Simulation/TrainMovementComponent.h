#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrainMovementComponent.generated.h"

class UTrackSplineComponent;
class AStationActor;

/**
 * Component that adds train movement capabilities to any actor.
 * Handles spline following, station stops, and basic collision avoidance.
 */
UCLASS(ClassGroup=(SwissTrain), meta=(BlueprintSpawnableComponent))
class SWISSTRAINRAIL_API UTrainMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTrainMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

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

	/**
	 * Update the owner actor's position based on the train movement.
	 */
	void UpdateTrainPosition();

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