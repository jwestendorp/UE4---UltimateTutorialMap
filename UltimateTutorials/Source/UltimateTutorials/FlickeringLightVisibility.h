

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

		void Tick(float DeltaSeconds);

public:
	UPROPERTY(VisibleAnywhere, Category = "Light")
		TSubobjectPtr<UPointLightComponent> lightComp;
	
};
