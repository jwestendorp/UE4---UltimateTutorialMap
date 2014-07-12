

#pragma once

#include "Engine/Light.h"
#include "FlickeringLightBrightness.generated.h"

/**
 * 
 */
UCLASS()
class AFlickeringLightBrightness : public ALight
{
	GENERATED_UCLASS_BODY()

		void Flicker();
		virtual void Tick(float DeltaSeconds) OVERRIDE;
		float RandomBrightness;
public:
		void Delay();
};
