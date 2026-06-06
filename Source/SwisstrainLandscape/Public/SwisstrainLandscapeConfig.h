#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DataAsset.h"
#include "SwisstrainLandscapeConfig.generated.h"

/**
 * Configuration asset for Swisstrain landscapes
 */
UCLASS(BlueprintType)
class SWISSTRAINLANDSCAPE_API USwisstrainLandscapeConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// Name of the Swiss region this landscape represents
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	FString RegionName;

	// Path to the elevation data file
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ElevationDataPath;

	// Base geographic coordinates
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geography")
	double Latitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geography")
	double Longitude;

	// Landscape dimensions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
	float Height;

	// Resolution settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resolution")
	int32 ResolutionX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resolution")
	int32 ResolutionY;

	// Default material layers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	TMap<FString, class UMaterialInterface*> MaterialLayers;

	// LOD settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOD")
	bool bEnableLOD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LOD")
	int32 MaxLODLevels;

	// Performance settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	bool bEnableOcclusionCulling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float TessellationFactor;
};