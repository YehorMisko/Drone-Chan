// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyShooterCharacter.generated.h"


class ADrone;
class AWeapon;
UCLASS()
class MYSHOOTER_API AMyShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyShooterCharacter();
	/*Fire function*/
	void FireWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;
	/*Camera that follow the character*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	/*Base turn rate, in deg/sec. Other scaling may affect final turn rate*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/*Base look up/down rate, in deg/sec. Other scaling may affect final turn rate*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)

		float BaseLookUpRate;

	/*Test if an input action is working*/
	void Test();
	/*Called for forwards/backwards input*/
	void MoveForward(float Value);

	/*Called for forwards/backwards input*/
	void MoveRight(float Value);

	/*
	Called via input to turn at a given rate.
	@param Rate This is a normalized rate, i.e 1.0 means 100% of desired turn rate
*/
	void TurnAtRate(float Rate);
	/*
	Called via input to look up/down at a given rate.
	@param Rate This is a normalized rate, i.e 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
		bool bAiming;

	/*Line trace for items under the corsshairs*/
	bool TraceUnderCrosshairs(FHitResult& OutHitResult);

	

	/*Toggle possession function*/
	void ToggleDrone();
	
	/*A test function to figure out if an axis is working*/
	void AxisTest(float Value);


	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Called when damage is taken
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
private:

	
	/*The weapon that the Character is holding*/
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY()
		AWeapon* Weapon;

	/*The drone that is going to be possessed*/
	UPROPERTY(EditDefaultsOnly, Category = Drone)
		TSubclassOf<ADrone> DroneClass;
	UPROPERTY()
		 ADrone* Drone;

	/*A check if the drone is possessed*/
	UPROPERTY()
		bool isOnDrone;
	/*Particle system for the Muzzle*/
	UPROPERTY(EditDefaultsOnly, Category = MuzzleFlash)
	class UParticleSystem* MuzzleFlash;

	/*Drone ammount*/
	int DroneAmmo;
	/*the health that the character starts with*/
	UPROPERTY(EditDefaultsOnly)
		float maxHealth;

	UPROPERTY(VisibleAnywhere)
		float health;
	//A function for what happens when the character dies
	void Death();
public:
	/*Returns CameraBoom subobject*/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/*Returns FollowCamera subobject*/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
