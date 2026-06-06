#pragma once

#include "CoreMinimal.h"
#include "Editor/EditorEngine.h"
#include "TrackEditorMode.generated.h"

class FTrackPlacementTool;
class FStationPlacementTool;

/**
 * Custom editor mode for railway track construction.
 * Provides specialized tools and visualization for building railway routes.
 */
UCLASS()
class SWISSTRAINRAIL_API UTrackEditorMode : public UEditorEngine
{
	GENERATED_BODY()

public:
	// Constructor
	UTrackEditorMode();

	//~ Begin UEditorEngine Interface
	virtual void Enter() override;
	virtual void Exit() override;
	virtual bool UsesTransformWidget() const override;
	virtual bool UsesToolkits() const override;
	//~ End UEditorEngine Interface

	/**
	 * Get the current track placement tool.
	 */
	TSharedPtr<FTrackPlacementTool> GetTrackPlacementTool() const { return TrackPlacementTool; }

	/**
	 * Get the current station placement tool.
	 */
	TSharedPtr<FStationPlacementTool> GetStationPlacementTool() const { return StationPlacementTool; }

private:
	// Track placement tool instance
	TSharedPtr<FTrackPlacementTool> TrackPlacementTool;

	// Station placement tool instance
	TSharedPtr<FStationPlacementTool> StationPlacementTool;
};