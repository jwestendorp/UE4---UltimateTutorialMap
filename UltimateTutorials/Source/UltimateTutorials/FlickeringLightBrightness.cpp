

#include "UltimateTutorials.h"
#include "FlickeringLightBrightness.h"


AFlickeringLightBrightness::AFlickeringLightBrightness(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP.SetDefaultSubobjectClass<UPointLightComponent>(TEXT("LightComponent0")))
{
	RootComponent = LightComponent;
}

void AFlickeringLightBrightness::Flicker()
{
	RandomBrightness = ((float)rand()) / ((float)(RAND_MAX / 5000.f));
	LightComponent->SetBrightness(RandomBrightness);
}

//Timer ; Delay

void AFlickeringLightBrightness::Delay()
{
	GetWorldTimerManager().SetTimer(this, &AFlickeringLightBrightness::Flicker, 0.01f, true);
}
void AFlickeringLightBrightness::BeginPlay()
{
	Delay();
}
