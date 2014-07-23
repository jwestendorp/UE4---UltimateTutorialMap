

#pragma once

#include "Engine/Light.h"
#include "FlickeringLightVisibility.generated.h"

/**
 * 
 */
UCLASS()
class AFlickeringLightVisibility : public ALight
{
	GENERATED_UCLASS_BODY()

		void BeginPlay();
		void Delay();
		void Flicker();
	
};

