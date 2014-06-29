

#pragma once

#include "GameFramework/CheatManager.h"
#include "UTMModifiers.generated.h"


/**
 * 
 */
UCLASS(Within = UTMController)
class UUTMModifiers : public UCheatManager
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(Exec)
	void TaxiCabNumber();

	UFUNCTION(Exec)
	void TheRedButton();

	UFUNCTION(Exec, BlueprintImplementableEvent)
	void HIMYM();
};
