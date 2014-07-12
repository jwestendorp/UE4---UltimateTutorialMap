

#include "UltimateTutorials.h"
#include "FlickeringLightVisibility.h"


AFlickeringLightVisibility::AFlickeringLightVisibility(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	lightComp = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, "BlinkLightV");
	RootComponent = lightComp;
}

void AFlickeringLightVisibility::BeginPlay()
{
	Delay();
}

void AFlickeringLightVisibility::Delay()
{
	GetWorldTimerManager().SetTimer(this, &AFlickeringLightVisibility::Flicker, 1.7f, true);
}

void AFlickeringLightVisibility::Flicker()
{
	lightComp->ToggleVisibility();
}