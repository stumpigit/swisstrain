#include "StationPlacementTool.h"
#include "EditorViewportClient.h"
#include "ScopedTransaction.h"

#define LOCTEXT_NAMESPACE "SwisstrainRail"

FStationPlacementTool::FStationPlacementTool()
{

}

FStationPlacementTool::~FStationPlacementTool()
{

}

void FStationPlacementTool::SetupForShiftClick(const FInputEventState& InputState)
{

}

bool FStationPlacementTool::CanDeferToEditorMode() const
{
	return true;
}

#undef LOCTEXT_NAMESPACE