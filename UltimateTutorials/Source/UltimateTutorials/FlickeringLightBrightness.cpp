

#include "UltimateTutorials.h"
#include "FlickeringLightBrightness.h"


AFlickeringLightBrightness::AFlickeringLightBrightness(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP.SetDefaultSubobjectClass<UPointLightComponent>(TEXT("LightComponent0")))
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = LightComponent;
}

void AFlickeringLightBrightness::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Flicker();
}

void AFlickeringLightBrightness::Flicker()
{
	RandomBrightness = ((float)rand()) / ((float)(RAND_MAX / 5000.f));
	LightComponent->SetBrightness(RandomBrightness);
}



