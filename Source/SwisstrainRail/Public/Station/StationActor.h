#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StationActor.generated.h"

class UStationAnchorComponent;

/**
 * Actor representing a railway station or halt point.
 * Can be placed independently or anchored to a track spline.
 */
UCLASS()
class SWISSTRAINRAIL_API AStationActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AStationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Anchor component for attaching to track splines.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Station", meta = (AllowPrivateAccess = "true"))
	UStationAnchorComponent* StationAnchor;

	/**
	 * Enum defining types of stations/halt points.
	 */
	enum class EStationType
	{
		MainStation,
		HaltPoint,
		Junction
	};

	/**
	 * Type of this station/halt point.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station Settings")
	EStationType StationType;

	/**
	 * Display name for this station.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station Settings")
	FString StationName;
};