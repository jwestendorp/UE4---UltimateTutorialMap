

#include "UltimateTutorials.h"
#include "DayTimeLight.h"


ADayTimeLight::ADayTimeLight(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP.SetDefaultSubobjectClass<UDirectionalLightComponent>(TEXT("LightComponent0")))
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = LightComponent;
	SunSpeed = 1.f;
	SetMobility(EComponentMobility::Movable);
	LightComponent->SetAffectDynamicIndirectLighting(true);
}

void ADayTimeLight::Tick(float DeltaSeconds){

	Super::Tick(DeltaSeconds);

	FRotator SunRot = GetActorRotation();
	MyRot.X += SunSpeed*DeltaSeconds;
	if (MyRot.X > 360)
		MyRot.X -= 360;
	SunRot.Pitch = MyRot.X;
	SunRot.Roll = MyRot.Y;
	SunRot.Yaw = MyRot.Z;
	SetActorRotation(SunRot);
	

}

void ADayTimeLight::BeginPlay()
{
	Super::BeginPlay();
	FRotator SunRot = GetActorRotation();
	MyRot.X = SunRot.Pitch;
	MyRot.Y = SunRot.Roll;
	MyRot.Z = SunRot.Yaw;
}
