#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackSplineActor.generated.h"

class UTrackSplineComponent;

/**
 * Actor representing a railway track route in the editor.
 * Contains a TrackSplineComponent for the actual spline data and provides
 * editor visualization and interaction capabilities.
 */
UCLASS()
class SWISSTRAINRAIL_API ATrackSplineActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ATrackSplineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Spline component that defines the track route.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Track", meta = (AllowPrivateAccess = "true"))
	UTrackSplineComponent* TrackSpline;

	/**
	 * Material to use for visualizing the track route in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track Visuals")
	UMaterialInterface* TrackVisualMaterial;
};