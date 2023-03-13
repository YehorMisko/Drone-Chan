// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAIController.h"

#include "Kismet/GameplayStatics.h"
void ACharacterAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ACharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	APawn* FocusPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //Get the player pawn
	if (LineOfSightTo(FocusPawn))
	{
		SetFocus(FocusPawn); //Set the focus on the player pawn
		MoveToActor(FocusPawn); //Follow the player pawn
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}

