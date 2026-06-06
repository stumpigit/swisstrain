#include "TrackPlacementTool.h"
#include "EditorViewportClient.h"
#include "ScopedTransaction.h"

#define LOCTEXT_NAMESPACE "SwisstrainRail"

FTrackPlacementTool::FTrackPlacementTool()
{

}

FTrackPlacementTool::~FTrackPlacementTool()
{

}

void FTrackPlacementTool::SetupForShiftClick(const FInputEventState& InputState)
{

}

bool FTrackPlacementTool::CanDeferToEditorMode() const
{
	return true;
}

#undef LOCTEXT_NAMESPACE