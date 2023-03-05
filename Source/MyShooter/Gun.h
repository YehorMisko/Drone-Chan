// Fill out your copyright notice in the Description page of Project Settings.

/*
To do: Merge this with the weapon class, as they should not be separate
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"
/*
To do: create a system where each blueprint that inherits this class has it's own damage values,
reload times, accuracy, recoil, ammo type, capacity etc.
*/
UCLASS()
class MYSHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/*Create a root scene Root Component*/
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	/*Create a mesh Component*/
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;
	
};
