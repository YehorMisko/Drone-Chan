// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include"Obstacle.h"
// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*Create the scene component and make it the root component*/
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);
	/*Create the spawn points and attach them to the scene component*/
	SpawnPoint1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Point 1"));
	SpawnPoint1->SetupAttachment(SceneComponent);
	SpawnPoint2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Point 2"));
	SpawnPoint2->SetupAttachment(SceneComponent);
	SpawnPoint3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Point 3"));
	SpawnPoint3->SetupAttachment(SceneComponent);
	
}

// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	/*Make a list of all spawn points coordinates*/
	listOfSpawnPoints = GetSpawnPoints();
	/*Starting in 2 seconds, spawn an Obstacle each 3 seconds*/
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AObstacleSpawner::SpawnObstacle, 3.0f, true, 2.0f);
}
//Get the x y z of all of all of the spawn points
TArray<FVector> AObstacleSpawner::GetSpawnPoints()
{
	TArray<FVector> spawnPointLoc;
	TArray<UArrowComponent*> arrowComponents;
	GetComponents<UArrowComponent>(arrowComponents);
	for (int i = 0; i < arrowComponents.Num(); i++)
	{
		spawnPointLoc.Add(arrowComponents[i]->GetRelativeLocation());
	}
	
	return spawnPointLoc;
}
/*Randomly spawn obstacle at one of the spawn points*/
void AObstacleSpawner::SpawnObstacle()
{
	Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstacleClass, listOfSpawnPoints[FMath::RandRange(0, listOfSpawnPoints.Num()-1)] + GetActorLocation(), GetActorRotation());
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

