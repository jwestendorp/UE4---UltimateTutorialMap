

#pragma once

#include "Engine/Light.h"
#include "FlickeringLightBrightness.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Lights, FlickeringLights), MinimalAPI)
class AFlickeringLightBrightness : public ALight
{
	GENERATED_UCLASS_BODY()

		void Flicker();
		virtual void BeginPlay() override;
		float RandomBrightness;
		void Delay();

};
