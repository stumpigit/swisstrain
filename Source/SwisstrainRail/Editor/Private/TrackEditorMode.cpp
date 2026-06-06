#include "TrackEditorMode.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "SwisstrainRail"

FTrackEditorMode::FTrackEditorMode()
{

}

FTrackEditorMode::~FTrackEditorMode()
{

}

void FTrackEditorMode::Enter()
{
	FEdMode::Enter();
}

void FTrackEditorMode::Exit()
{
	FEdMode::Exit();
}

bool FTrackEditorMode::UsesToolkits() const
{
	return true;
}

#undef LOCTEXT_NAMESPACE