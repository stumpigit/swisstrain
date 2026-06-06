#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficControllerActor.generated.h"

class ATrainActor;
class UTrainMovementComponent;
class UTrackSplineComponent;

/**
 * Actor that manages traffic control for trains to prevent collisions.
 * Implements a simple reservation system for track segments.
 */
UCLASS()
class SWISSTRAINRAIL_API ATrafficControllerActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ATrafficControllerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Register a train with the traffic controller.
	 */
	UFUNCTION(BlueprintCallable, Category = "Traffic Control")
	void RegisterTrain(ATrainActor* Train);

	/**
	 * Unregister a train from the traffic controller.
	 */
	UFUNCTION(BlueprintCallable, Category = "Traffic Control")
	void UnregisterTrain(ATrainActor* Train);

	/**
	 * Register a train movement component with the traffic controller.
	 */
	UFUNCTION(BlueprintCallable, Category = "Traffic Control")
	void RegisterTrainMovement(UTrainMovementComponent* TrainMovement);

	/**
	 * Unregister a train movement component from the traffic controller.
	 */
	UFUNCTION(BlueprintCallable, Category = "Traffic Control")
	void UnregisterTrainMovement(UTrainMovementComponent* TrainMovement);

	/**
	 * Request reservation for a track segment.
	 * @param Train The train requesting the reservation
	 * @param TrackSpline The spline the train is on
	 * @param StartDistance Start of the segment to reserve
	 * @param EndDistance End of the segment to reserve
	 * @return True if reservation was granted, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "Traffic Control")
	bool RequestTrackReservation(ATrainActor* Train, UTrackSplineComponent* TrackSpline, float StartDistance, float EndDistance);

	/**
	 * Release a track segment reservation.
	 * @param Train The train releasing the reservation
	 * @param TrackSpline The spline the train is on
	 * @param StartDistance Start of the segment to release
	 * @param EndDistance End of the segment to release
	 */
	UFUNCTION(BlueprintCallable, Category = "Traffic Control")
	void ReleaseTrackReservation(ATrainActor* Train, UTrackSplineComponent* TrackSpline, float StartDistance, float EndDistance);

private:
	// Structure to represent a reserved track segment
	struct FTrackReservation
	{
		ATrainActor* ReservedBy;
		UTrackSplineComponent* TrackSpline;
		float StartDistance;
		float EndDistance;
		float ReservationTime;

		FTrackReservation()
			: ReservedBy(nullptr)
			, TrackSpline(nullptr)
			, StartDistance(0.0f)
			, EndDistance(0.0f)
			, ReservationTime(0.0f)
		{
		}

		FTrackReservation(ATrainActor* InReservedBy, UTrackSplineComponent* InTrackSpline, float InStartDistance, float InEndDistance)
			: ReservedBy(InReservedBy)
			, TrackSpline(InTrackSpline)
			, StartDistance(InStartDistance)
			, EndDistance(InEndDistance)
			, ReservationTime(0.0f)
		{
		}
	};

	// List of registered trains
	UPROPERTY()
	TArray<ATrainActor*> RegisteredTrains;

	// List of registered train movement components
	UPROPERTY()
	TArray<UTrainMovementComponent*> RegisteredTrainMovements;

	// List of track reservations
	UPROPERTY()
	TArray<FTrackReservation> TrackReservations;

	// Time before an unused reservation expires (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Control")
	float ReservationTimeout;

	// Check for and clean up expired reservations
	void CleanupExpiredReservations(float DeltaTime);
};