#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RailConstructionHelper.generated.h"

class UTrackSplineComponent;

/**
 * Utility class providing visual feedback and assistance for railway construction.
 * Helps users make informed decisions about track placement and construction features.
 */
UCLASS()
class SWISSTRAINRAIL_API URailConstructionHelper : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Structure representing visual feedback for construction decisions.
	 */
	struct FConstructionFeedback
	{
		// Location where feedback applies
		FVector Location;

		// Type of visual feedback
		enum EFeedbackType
		{
			ValidPlacement,
			InvalidGrade,
			BridgeRequired,
			TunnelRequired,
			CutRequired,
			EmbankmentRequired
		} FeedbackType;

		// Descriptive message for the feedback
		FString Message;

		// Color to use for visual feedback
		FLinearColor FeedbackColor;
	};

	/**
	 * Generate visual feedback for track placement along a spline.
	 * @param TrackSpline The spline to analyze
	 * @param FeedbackDistance Distance between feedback points
	 * @return Array of construction feedback items
	 */
	UFUNCTION(BlueprintCallable, Category = "Construction Feedback")
	TArray<FConstructionFeedback> GeneratePlacementFeedback(
		UTrackSplineComponent* TrackSpline,
		float FeedbackDistance = 200.0f);

	/**
	 * Get appropriate visual color for a construction feature.
	 * @param FeatureType Type of construction feature
	 * @return Color to use for visualizing this feature
	 */
	UFUNCTION(BlueprintCallable, Category = "Visual Feedback")
	FLinearColor GetFeatureColor(EConstructionFeatureType FeatureType) const;

	/**
	 * Enum defining types of construction features for visualization.
	 */
	enum class EConstructionFeatureType
	{
		ValidTrack,
		InvalidGrade,
		Bridge,
		Tunnel,
		Cut,
		Embankment
	};
};