#pragma once

#include "CoreMinimal.h"
#include "InteractiveTool.h"
#include "TrackPlacementTool.generated.h"

class UTrackSplineComponent;

/**
 * Interactive tool for placing and editing railway track splines in the editor.
 * Provides snapping, grade limiting, and visual feedback during placement.
 */
UCLASS()
class SWISSTRAINRAIL_API UTrackPlacementTool : public UInteractiveTool
{
	GENERATED_BODY()

public:
	//~ Begin UInteractiveTool Interface
	virtual void Setup() override;
	virtual void Shutdown() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool CanDeactivate() const override;
	//~ End UInteractiveTool Interface

	/**
	 * Maximum allowed grade (slope) for the railway track, in degrees.
	 */
	UPROPERTY(EditAnywhere, Category = "Track Settings")
	float MaxGradeDegrees = 3.0f;

	/**
	 * Height offset from terrain surface when following landscape.
	 */
	UPROPERTY(EditAnywhere, Category = "Track Settings")
	float TerrainFollowOffset = 100.0f;

	/**
	 * Distance threshold for automatic bridge/tunnel decisions.
	 */
	UPROPERTY(EditAnywhere, Category = "Construction Decisions")
	float BridgeTunnelThreshold = 500.0f;

private:
	// Current spline being edited
	UTrackSplineComponent* CurrentSpline;

	// Temporary visualization for proposed track
	TArray<FVector> ProposedTrackPoints;
};