

#include "UltimateTutorials.h"
#include "FlickeringLightBrightness.h"


AFlickeringLightBrightness::AFlickeringLightBrightness(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	lightComp = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, "BlinkLightB");
	RootComponent = lightComp;
}

void AFlickeringLightBrightness::Tick(float DeltaSeconds)
{
	Flicker();
}


void AFlickeringLightBrightness::Flicker()
{
	RandomBrightness = ((float)rand()) / ((float)(RAND_MAX / 5000.f));
	lightComp->SetBrightness(RandomBrightness);
}

//void AFlickeringLightBrightness::Delay()
//{
//	GetWorldTimerManager().SetTimer(this, &AFlickeringLightBrightness::Flicker, 0.f, true);
//}
