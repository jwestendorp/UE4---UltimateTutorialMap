// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "UltimateTutorialsCharacter.generated.h"

UCLASS(config=Game)
class AUltimateTutorialsCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> FollowCamera;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	


	

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	//Sprinting
	void Sprint();
	void SprintEnd();
	void Jog();
	void Walk();
	bool bJogging;
	float Speed;
	float LastSpeed;

	//common Voids
	virtual void BeginPlay();
	
	//Zoomable Third Person
	float Zoom;
	FVector FpsOffset = FVector(-2.f, -7.f, 0.f);
	FVector TpsOffset = FVector(0.f, 30.f, 80.f);
	void ZoomIn();
	void ZoomOut();
	void updateCamera();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Variables)
		bool bIsInFPS;

		//Slow-Mo
		void SlowMo();
		bool bSlowMo;

	//HP, Death, Checkpoint, Respawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
		int32 DamageTaken;

		
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;
	// End of APawn interface
};

