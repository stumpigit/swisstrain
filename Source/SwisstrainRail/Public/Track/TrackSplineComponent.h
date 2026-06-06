#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "TrackSplineComponent.generated.h"

/**
 * Enhanced spline component specifically designed for railway track placement.
 * Provides railway-specific functionality like grade limiting, terrain following,
 * and construction decision support.
 */
UCLASS(ClassGroup=(SwissTrain), meta=(BlueprintSpawnableComponent))
class SWISSTRAINRAIL_API UTrackSplineComponent : public USplineComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTrackSplineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Maximum allowed grade (slope) for the railway track, in degrees.
	 * Used to prevent unrealistic track grades that would be impossible for trains.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track Settings")
	float MaxGradeDegrees = 3.0f;

	/**
	 * Height offset from terrain surface when following landscape.
	 * Allows tracks to appear slightly above ground level.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track Settings")
	float TerrainFollowOffset = 100.0f;

	/**
	 * Distance threshold for automatic bridge/tunnel decisions.
	 * When terrain difference exceeds this value, system will suggest
	 * bridge or tunnel construction.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Construction Decisions")
	float BridgeTunnelThreshold = 500.0f;

	/**
	 * Recalculate spline points to respect maximum grade limits.
	 * Should be called after manually adjusting control points.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Track Operations")
	void RecalculateWithGradeLimits();

	/**
	 * Analyze terrain along spline and identify construction features needed.
	 * Populates the ConstructionFeatures array with Bridge, Tunnel, Cut, and Embankment locations.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Construction Analysis")
	void AnalyzeConstructionFeatures();

	/**
	 * Structure to represent a construction feature along the track.
	 */
	struct FConstructionFeature
	{
		// Type of construction feature
		enum EFeatureType
		{
			Bridge,
			Tunnel,
			Cut,
			Embankment
		};

		// Location along the spline where feature occurs
		float DistanceAlongSpline;

		// Type of construction feature
		EFeatureType FeatureType;

		// Length of the construction feature
		float Length;
	};

	/**
	 * Array of construction features identified along the track.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Construction Analysis")
	TArray<FConstructionFeature> ConstructionFeatures;

private:
	/**
	 * Helper function to adjust spline point to maintain grade limits.
	 */
	void AdjustPointForGradeLimit(int32 PointIndex);

	/**
	 * Helper function to calculate terrain height at spline point.
	 */
	float GetTerrainHeightAtSplinePoint(int32 PointIndex);
};