// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"
class AObstacle;
UCLASS()
class MYSHOOTER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*Create a dummy component to attach the others*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USceneComponent* SceneComponent;
	/*Create spawn points*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UArrowComponent* SpawnPoint1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UArrowComponent* SpawnPoint2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UArrowComponent* SpawnPoint3;

private:
	/*Create a refrence to the spawnable Obstacle*/
	TArray<FVector> GetSpawnPoints();
	UPROPERTY(EditDefaultsOnly, Category = Obstacle)
		TSubclassOf<AObstacle> ObstacleClass;
	
	UPROPERTY()
		AObstacle* Obstacle;
	/*List of the spawn points*/
	TArray<FVector> listOfSpawnPoints;
	/*Function to randomly spawn obstacles*/
	void SpawnObstacle();
	/*Timer Handler*/
	FTimerHandle MemberTimerHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
