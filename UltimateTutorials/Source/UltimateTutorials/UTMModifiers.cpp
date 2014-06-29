

#include "UltimateTutorials.h"
#include "UTMCharacter.h"
#include "UTMModifiers.h"


UUTMModifiers::UUTMModifiers(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	
}

void UUTMModifiers::TaxiCabNumber()
{
	AUTMCharacter *MyCharacter = (AUTMCharacter*)GetWorld()->GetFirstPlayerController()->GetPawn();
	MyCharacter->Health = 1729;
}

void UUTMModifiers::TheRedButton()
{

}
