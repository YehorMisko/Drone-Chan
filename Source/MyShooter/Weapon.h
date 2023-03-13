// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "DrawDebugHelpers.h"
#include "Weapon.generated.h"
/*

*/
UCLASS()
class MYSHOOTER_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWeapon();
	//The shoot function
	void PullTrigger();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/*Particle system for the Muzzle*/
	UPROPERTY(EditAnywhere, Category = Particles)
		class UParticleSystem* MuzzleFlash;
	/*Particle system for hit visualisation*/
	UPROPERTY(EditAnywhere, Category = Particle)
	class UParticleSystem* ImpactEffect;
	/*Max bullet range for the weapon*/
	UPROPERTY(EditAnywhere, Category = GunCharacteristics)
		float maxRange;
	/*Damage dealt by the weapon*/
	UPROPERTY(EditAnywhere, Category = GunCharacteristics)
		float damage;
	/*Fire Rate of the weapon in seconds to wait for another shot*/
	UPROPERTY(EditAnywhere, Category = GunCharacteristics)
		float fireRate;
	/*Create a timer Handle for fire rate*/
	FTimerHandle FireTimerHandle;

	/*Check if the gun can shoot*/
	bool canShoot;
};
