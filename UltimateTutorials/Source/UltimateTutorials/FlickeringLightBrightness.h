

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

		void Tick(float DeltaSeconds);
		void Flicker();
		/*void Delay();*/
		float RandomBrightness;

	public:
		UPROPERTY(VisibleAnywhere, Category = "Light")
		TSubobjectPtr<UPointLightComponent> lightComp;
	
		
	
};
