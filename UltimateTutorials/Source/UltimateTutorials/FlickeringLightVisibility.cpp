

#include "UltimateTutorials.h"
#include "FlickeringLightVisibility.h"


AFlickeringLightVisibility::AFlickeringLightVisibility(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	lightComp = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, "BlinkLightV");
	RootComponent = lightComp;
}

void AFlickeringLightVisibility::Tick(float DeltaSeconds)
{
	lightComp->ToggleVisibility();
}
