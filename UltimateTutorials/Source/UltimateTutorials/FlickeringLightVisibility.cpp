

#include "UltimateTutorials.h"
#include "FlickeringLightVisibility.h"


AFlickeringLightVisibility::AFlickeringLightVisibility(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP.SetDefaultSubobjectClass<UPointLightComponent>(TEXT("LightComponent0")))
{
	RootComponent = LightComponent;
}

void AFlickeringLightVisibility::BeginPlay()
{
	Delay();
}

void AFlickeringLightVisibility::Delay()
{
	GetWorldTimerManager().SetTimer(this, &AFlickeringLightVisibility::Flicker, 0.01f, true);
}

void AFlickeringLightVisibility::Flicker()
{
	LightComponent->ToggleVisibility();
}