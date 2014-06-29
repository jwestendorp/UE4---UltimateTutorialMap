// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UltimateTutorials.h"
#include "UTMGameMode.h"

AUTMGameMode::AUTMGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UClass> PlayerPawnBPClass(TEXT("Class'/Game/Blueprints/UTM_Char.UTM_Char_C'"));
	if (PlayerPawnBPClass.Object != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Object;

	}
}
