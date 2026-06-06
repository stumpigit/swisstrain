#pragma once

#include "CoreMinimal.h"
#include "EditorModeBase.h"
#include "SwisstrainLandscapeEditorMode.generated.h"

class FEdMode;

/**
 * Editor mode for Swisstrain landscape sculpting
 */
UCLASS()
class SWISSTRAINLANDSCAPE_API USwisstrainLandscapeEditorMode : public UEditorModeBase
{
	GENERATED_BODY()

public:
	USwisstrainLandscapeEditorMode();

	//~ Begin UEditorModeBase Interface
	virtual void Enter() override;
	virtual void Exit() override;
	virtual bool UsesTransformWidget() const override;
	virtual bool UsesToolkits() const override;
	//~ End UEditorModeBase Interface
};