#include "Track/TrackSplineActor.h"
#include "Track/TrackSplineComponent.h"
#include "Components/SplineComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATrackSplineActor::ATrackSplineActor()
{
	PrimaryActorTick.bCanEverTick = true;

	TrackSpline = CreateDefaultSubobject<UTrackSplineComponent>(TEXT("Track Spline"));
	RootComponent = TrackSpline;
}

// Called when the game starts or when spawned
void ATrackSplineActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrackSplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}