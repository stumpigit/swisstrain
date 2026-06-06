#include "Station/StationActor.h"
#include "Station/StationAnchorComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AStationActor::AStationActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StationAnchor = CreateDefaultSubobject<UStationAnchorComponent>(TEXT("StationAnchor"));
	StationAnchor->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStationActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}