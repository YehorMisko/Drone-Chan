// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
void ACharacterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior); //If a tree is not null set it as the Behavior for the AI

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation()); //Set the key to pawn's starting location

	}
}

void ACharacterAIController::Tick(float DeltaTime)
{
 	Super::Tick(DeltaTime);
	
	

}

