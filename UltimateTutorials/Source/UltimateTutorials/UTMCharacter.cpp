// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UltimateTutorials.h"
#include "UTMCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AUTMCharacter

AUTMCharacter::AUTMCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	Zoom = 50.f;


	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;
	CharacterMovement->MaxWalkSpeed = 300.f;
	
	//shooting
	//G36CSpeed = 4.f;

	//damage, checkpoint, respawn
	Health = 1000.f;
	DamageTaken = 0.f;

	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUseControllerViewRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUseControllerViewRotation = true; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUTMCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AUTMCharacter::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AUTMCharacter::SprintEnd);
	InputComponent->BindAction("Jog", IE_Pressed, this, &AUTMCharacter::Jog);

	InputComponent->BindAction("SlowMo", IE_Pressed, this, &AUTMCharacter::SlowMo);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AUTMCharacter::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AUTMCharacter::ZoomOut);

	InputComponent->BindAxis("MoveForward", this, &AUTMCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUTMCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AUTMCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AUTMCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUTMCharacter::TouchStarted);
}

void AUTMCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AUTMCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUTMCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUTMCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && bAllowInput == true)
	{
		//swimming
		if (GetPawnPhysicsVolume()->bWaterVolume)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
			return;
		}

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUTMCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && bAllowInput == true)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AUTMCharacter::Sprint()
{
	Speed = 1200.f;
	CharacterMovement->MaxWalkSpeed = Speed;
}

void AUTMCharacter::SprintEnd()
{
	Speed = LastSpeed;
	CharacterMovement->MaxWalkSpeed = Speed;
}

void AUTMCharacter::Jog()
{
	bJogging = !bJogging;

	if (bJogging)
	{
		Speed = 800.f;
		CharacterMovement->MaxWalkSpeed = Speed;
		LastSpeed = Speed;
	}
	else
	{
		Walk();
	}
}

void AUTMCharacter::Walk()
{
	Speed = 300.f;
	CharacterMovement->MaxWalkSpeed = Speed;
	LastSpeed = Speed;
}

void AUTMCharacter::ZoomIn()
{


	if (CameraBoom->TargetArmLength > 50.f)
	{
		bIsInFPS = false;
		CameraBoom->TargetArmLength -= Zoom;
		CameraBoom->AttachTo(RootComponent);
		CameraBoom->SetRelativeLocation(TpsOffset);
		bUseControllerRotationYaw = false;
	}
	else
	{
		bIsInFPS = true;
		CameraBoom->AttachTo(Mesh, "fpsHead");
		CameraBoom->TargetArmLength = 0.f;
		bUseControllerRotationYaw = true;
		CameraBoom->SetRelativeLocation(FpsOffset);
	}
}

void AUTMCharacter::ZoomOut()
{


	if (CameraBoom->TargetArmLength < 300.f)
	{
		bIsInFPS = false;
		CameraBoom->TargetArmLength += Zoom;
		CameraBoom->AttachTo(RootComponent);
		CameraBoom->SetRelativeLocation(TpsOffset);
		bUseControllerRotationYaw = false;
	}
}

void AUTMCharacter::SlowMo()
{
	bSlowMo = !bSlowMo;

	if (bSlowMo == true)
	{
		UGameplayStatics::SetGlobalTimeDilation(this, 0.3f);
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(this, 1.f);
	}
}





void AUTMCharacter::BeginPlay()
{
	LastSpeed = 300.f;
	bIsInFPS = true;
	CameraBoom->AttachTo(Mesh, "fpsHead");
	CameraBoom->TargetArmLength = 0.f;
	bUseControllerRotationYaw = true;
	CameraBoom->SetRelativeLocation(FpsOffset);
	bAllowInput = true;
}






void AUTMCharacter::TakeDmg_Implementation(int32 Damage)
{
	DamageTaken = Damage;
	Health = Health - DamageTaken;
	if (Health < 0)
	{
		Health = 0;
	}
}
