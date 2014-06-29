// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "UTMCharacter.generated.h"

UENUM(BlueprintType, Category = "Weapons")
enum EWeaponTypes
{
	None,
	G36C
};



UCLASS(config=Game)
class AUTMCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()



	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		TSubobjectPtr<class UCameraComponent> FollowCamera;

protected:

	// APawn interface
		virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;
	// End of APawn interface

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

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	//Sprinting
	void Sprint();
	void SprintEnd();
	void Jog();
	void Walk();
	bool bJogging;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variables")
		bool bAllowInput;
	float Speed;
	float LastSpeed;

	//Zoomable Third Person
	float Zoom;
	FVector FpsOffset = FVector(-2.f, -7.f, 0.f);
	FVector TpsOffset = FVector(0.f, 30.f, 80.f);
	void ZoomIn();
	void ZoomOut();
	void updateCamera();

	//Slow-Mo
	void SlowMo();
	bool bSlowMo;


	////Shooting
	//UPROPERTY(EditAnywhere, Category = "Weapons", BlueprintReadWrite)
	//UStaticMesh* WeaponMesh;
	//UPROPERTY(EditAnywhere, Category = "Weapons", BlueprintReadWrite)
	//UParticleSystem* MuzzleFlash;

	//bool bPressed;
	//bool bPlaynAnim;
	//
	//float RateOfFire;
	//float HeatSpeed;
	//float HeatLevel;
	//float MaxSpread;
	//float Spread;
	//float SpreadChange;
	//float HiRot;
	//float HiRotTarget;
	//float HiRotSpeed;
	//float HiRotPlayer;
	//float GunDeltaTime;
	//
	//int32 AmmoNow;
	//int32 AmmoMax;
	//int32 DamageMin;
	//int32 DamageMax;

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapons")
	//void ChangeWeapon(EWeaponTypes WeaponType);



	//common Voids
	virtual void BeginPlay();
	
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ZoomTPS")
		bool bIsInFPS;

	

	//HP, Death, Checkpoint, Respawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DmgSystem")
	int32 DamageTaken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DmgSystem")
	bool bHasDied;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DmgSystem")
		int32 Health;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DmgSystem")
		void TakeDmg(int32 Damage);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DmgSystem")
		void Respawn();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DmgSystem")
		void PlayDmgSound();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DmgSystem")
		void PlayRespawnSound();


};
