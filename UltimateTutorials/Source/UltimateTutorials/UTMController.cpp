

#include "UltimateTutorials.h"
#include "UTMController.h"
#include "UTMModifiers.h"


AUTMController::AUTMController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CheatClass = UUTMModifiers::StaticClass();
}


