#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StationAnchorComponent.generated.h"

class UTrackSplineComponent;

/**
 * Component for anchoring stations to track splines.
 * Handles automatic positioning and orientation of stations along tracks.
 */
UCLASS(ClassGroup=(SwissTrain), meta=(BlueprintSpawnableComponent))
class SWISSTRAINRAIL_API UStationAnchorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStationAnchorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Spline component this station is anchored to.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchor Settings")
	UTrackSplineComponent* AnchoredSpline;

	/**
	 * Distance along the spline where this station is positioned.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchor Settings")
	float DistanceAlongSpline = 0.0f;

	/**
	 * Automatically orient the station to match the track direction.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anchor Settings")
	bool bAutoOrientToTrack = true;

	/**
	 * Update station position and orientation based on spline attachment.
	 */
	UFUNCTION(BlueprintCallable, Category = "Anchor Operations")
	void UpdateAnchorPosition();

	/**
	 * Snap to the nearest point on the specified spline.
	 */
	UFUNCTION(BlueprintCallable, Category = "Anchor Operations")
	void SnapToNearestSplinePoint(UTrackSplineComponent* TargetSpline);
};