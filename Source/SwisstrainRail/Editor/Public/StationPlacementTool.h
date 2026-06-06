#pragma once

#include "CoreMinimal.h"
#include "InteractiveTool.h"
#include "StationPlacementTool.generated.h"

class AStationActor;

/**
 * Interactive tool for placing and editing railway stations in the editor.
 * Provides snapping to tracks and automatic orientation.
 */
UCLASS()
class SWISSTRAINRAIL_API UStationPlacementTool : public UInteractiveTool
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
	 * Enum defining types of stations that can be placed.
	 */
	enum class EStationPlacementType
	{
		MainStation,
		HaltPoint,
		Junction
	};

	/**
	 * Type of station to place.
	 */
	UPROPERTY(EditAnywhere, Category = "Station Settings")
	EStationPlacementType StationType = EStationPlacementType::HaltPoint;

private:
	// Current station being placed
	AStationActor* CurrentStation;
};