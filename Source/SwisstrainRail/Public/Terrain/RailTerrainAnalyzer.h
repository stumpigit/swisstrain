#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RailTerrainAnalyzer.generated.h"

class ULandscape;

/**
 * Utility class for analyzing terrain along a proposed railway route.
 * Identifies where bridges, tunnels, cuts, and embankments would be needed.
 */
UCLASS()
class SWISSTRAINRAIL_API URailTerrainAnalyzer : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Structure representing analysis results for a segment of track.
	 */
	struct FTrackSegmentAnalysis
	{
		// Start and end distances along the spline
		float StartDistance;
		float EndDistance;

		// Average terrain height along this segment
		float AverageTerrainHeight;

		// Maximum deviation from average height
		float MaxHeightDeviation;

		// Recommended construction feature (if any)
		enum ERecommendedFeature
		{
			None,
			Bridge,
			Tunnel,
			Cut,
			Embankment
		} RecommendedFeature;

		// Length of the recommended construction feature
		float FeatureLength;
	};

	/**
	 * Analyze terrain along a proposed railway route.
	 * @param Landscape The landscape to analyze
	 * @param SplinePoints Array of points defining the proposed track route
	 * @param AnalysisDistance Sample distance for terrain analysis
	 * @return Array of analysis results for track segments
	 */
	UFUNCTION(BlueprintCallable, Category = "Terrain Analysis")
	TArray<FTrackSegmentAnalysis> AnalyzeRailRoute(
		ULandscape* Landscape,
		const TArray<FVector>& SplinePoints,
		float AnalysisDistance = 100.0f);

	/**
	 * Calculate if a bridge is needed at a specific point.
	 * @param TerrainHeight Actual terrain height at point
	 * @param TrackHeight Desired track height at point
	 * @param BridgeThreshold Height difference that requires a bridge
	 * @return True if a bridge is recommended
	 */
	UFUNCTION(BlueprintCallable, Category = "Feature Detection")
	bool IsBridgeNeeded(float TerrainHeight, float TrackHeight, float BridgeThreshold = 500.0f) const;

	/**
	 * Calculate if a tunnel is needed at a specific point.
	 * @param TerrainHeight Actual terrain height at point
	 * @param TrackHeight Desired track height at point
	 * @param TunnelThreshold Height difference that requires a tunnel
	 * @return True if a tunnel is recommended
	 */
	UFUNCTION(BlueprintCallable, Category = "Feature Detection")
	bool IsTunnelNeeded(float TerrainHeight, float TrackHeight, float TunnelThreshold = 500.0f) const;
};