// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AWeapon::AWeapon()
{
	maxRange = 10000.0f;
	damage = 10.0f;
	fireRate = 2.0f;
	canShoot = true;
}

void AWeapon::PullTrigger()
{
	/*Check if timer running*/
	if(canShoot)
	{
		/*Start the timer*/
		GetWorldTimerManager().SetTimer(FireTimerHandle, fireRate,false,0);
		/*Spawn a muzzle at the end of the barell*/
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, ItemMesh, TEXT("BarrelSocket"));
			/*Get the owner*/
			APawn* OwnerPawn = Cast<APawn>(GetOwner()); //this is different to what I've written in the drone class, but works the same
			if (OwnerPawn == nullptr)return; //If the owner does not exist return early
			AController* OwnerController = OwnerPawn->GetController(); //Get the contorller
			if (OwnerController == nullptr) return;
			//Get Location and Rotation of the player's camera
				FVector Location;
		FRotator Rotation;
		OwnerController->GetPlayerViewPoint(Location, Rotation);

		/*Get the end location of the trace*/
		FVector End = Location + Rotation.Vector() * maxRange;

		FHitResult Hit;
		//Do a trace
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
		//Check if you hit something

		if (bSuccess)
		{
			//DrawDebugPoint(GetWorld(), Hit.Location, 40, FColor::Red, true); debug code

			FVector ShotDirection = -Rotation.Vector(); //the direction from which the shot is coming from
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());



			//If an actor was hit
			AActor* HitActor = Hit.GetActor();
			if (HitActor != nullptr)
			{
				//Damage Event init
				FString name = HitActor->GetFName().ToString();
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, name); debug code
				FPointDamageEvent DamageEvent(damage, Hit, ShotDirection, nullptr);
				HitActor->TakeDamage(damage, DamageEvent, OwnerController, this); //Deal damage to the actor

			}
		}
	}
	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
