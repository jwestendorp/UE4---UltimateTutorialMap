

#pragma once

#include "Engine/Light.h"
#include "DayTimeLight.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Lights, DayTimeLights), MinimalAPI, meta = (ChildCanTick))
class ADayTimeLight : public ALight
{
	
		GENERATED_UCLASS_BODY()
			
			
		void Tick(float DeltaSeconds) OVERRIDE;
	

		virtual void BeginPlay() OVERRIDE;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variable")
		float SunSpeed;
			
	private:
		FVector MyRot;
	

		

};
