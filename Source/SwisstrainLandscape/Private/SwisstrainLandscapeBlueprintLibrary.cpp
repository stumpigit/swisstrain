#include "SwisstrainLandscapeBlueprintLibrary.h"
#include "Engine/World.h"
#include "Landscape.h"
#include "SwisstopoLandscapeDataProvider.h"
#include "SwisstrainSculptingTools.h"
#include "SwisstrainTexturingSystem.h"
#include "SwisstrainLODSystem.h"

bool USwisstrainLandscapeBlueprintLibrary::CreateSwissLandscapeFromData(
	UObject* WorldContextObject,
	const FString& ElevationDataPath,
	FVector Location,
	FRotator Rotation,
	FVector Scale,
	ALandscape*& OutLandscape)
{
	if (!WorldContextObject)
	{
		return false;
	}

	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		return false;
	}

	// Create landscape actor
	OutLandscape = World->SpawnActor<ALandscape>(Location, Rotation);
	if (!OutLandscape)
	{
		return false;
	}

	// Scale the landscape
	OutLandscape->SetActorScale3D(Scale);

	// Load elevation data and generate landscape
	// In a real implementation, this would use the Swisstopo data provider
	
	return true;
}

bool USwisstrainLandscapeBlueprintLibrary::SculptSwissLandscape(
	ALandscape* TargetLandscape,
	FVector WorldPosition,
	float BrushRadius,
	float BrushStrength,
	int32 ToolType,
	int32 FalloffType)
{
	if (!TargetLandscape)
	{
		return false;
	}

	ESculptingToolType ToolTypeEnum = static_cast<ESculptingToolType>(ToolType);
	EBrushFalloffType FalloffTypeEnum = static_cast<EBrushFalloffType>(FalloffType);

	return USwisstrainSculptingTools::ApplySculptingOperation(
		TargetLandscape,
		WorldPosition,
		BrushRadius,
		BrushStrength,
		ToolTypeEnum,
		FalloffTypeEnum);
}

bool USwisstrainLandscapeBlueprintLibrary::TextureSwissLandscape(
	ALandscape* TargetLandscape,
	int32 LayerType,
	UMaterialInterface* Material,
	FString LayerName)
{
	if (!TargetLandscape)
	{
		return false;
	}

	ELandscapeMaterialLayer LayerTypeEnum = static_cast<ELandscapeMaterialLayer>(LayerType);

	return USwisstrainTexturingSystem::ApplyMaterialLayer(
		TargetLandscape,
		LayerTypeEnum,
		Material,
		LayerName);
}

bool USwisstrainLandscapeBlueprintLibrary::OptimizeSwissLandscapeLOD(
	ALandscape* TargetLandscape,
	float ViewDistance)
{
	if (!TargetLandscape)
	{
		return false;
	}

	// Calculate and apply optimal LOD settings for Swiss terrain
	FLandscapeLODSettings OptimalSettings = USwisstrainLODSystem::CalculateOptimalLODSettings(
		ViewDistance,
		TargetLandscape->GetActorScale3D().GetMax() * 1000.0f); // Approximate size

	return USwisstrainLODSystem::ApplyLODSettings(TargetLandscape, OptimalSettings);
}