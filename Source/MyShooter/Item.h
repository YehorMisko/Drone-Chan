// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class MYSHOOTER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties")
		USkeletalMeshComponent* ItemMesh;
	/*Line Trace collides with box to show HUD widgets, uneeded for now*/
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	//	class UBoxComponent* CollisionBox;

	/*Popup widget*/
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UWidgetComponent* PickupWidget;
	/*Scene Component*/
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	
public:

};
