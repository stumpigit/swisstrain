#include "Editor/SwisstrainLandscapeEditorMode.h"

USwisstrainLandscapeEditorMode::USwisstrainLandscapeEditorMode()
{
	// Set the mode identifier
	Info.Name = FName(TEXT("SwisstrainLandscapeEditorMode"));
	Info.bVisible = true;
	Info.bAutoActivate = false;
}

void USwisstrainLandscapeEditorMode::Enter()
{
	UEditorModeBase::Enter();
	
	// In a real implementation, this would set up the landscape editing tools
	// and UI for the Swisstrain landscape system
}

void USwisstrainLandscapeEditorMode::Exit()
{
	// In a real implementation, this would clean up the landscape editing tools
	// and UI for the Swisstrain landscape system
	
	UEditorModeBase::Exit();
}

bool USwisstrainLandscapeEditorMode::UsesTransformWidget() const
{
	return false;
}

bool USwisstrainLandscapeEditorMode::UsesToolkits() const
{
	return true;
}