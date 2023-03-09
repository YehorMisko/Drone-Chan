// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleDeathTrigger.h"
#include "Components/BoxComponent.h"
// Sets default values
AObstacleDeathTrigger::AObstacleDeathTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Obstacle Death"));
	SetRootComponent(CollisionBox);
}

// Called when the game starts or when spawned
void AObstacleDeathTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleDeathTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

