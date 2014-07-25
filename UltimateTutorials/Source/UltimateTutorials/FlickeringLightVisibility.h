

#pragma once

#include "Engine/Light.h"
#include "FlickeringLightVisibility.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Lights, FlickeringLights), MinimalAPI)
class AFlickeringLightVisibility : public ALight
{
	GENERATED_UCLASS_BODY()

		void BeginPlay();
		void Delay();
		void Flicker();
	
};

