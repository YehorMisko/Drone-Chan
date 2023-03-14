// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PLayerLocationIfSeen.h"
#include"BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include"GameFramework/Pawn.h"
#include"Kismet/GameplayStatics.h"

UBTService_PLayerLocationIfSeen::UBTService_PLayerLocationIfSeen()
{
	NodeName = TEXT("Update If the player is seen");
}

void UBTService_PLayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AIPawn = OwnerComp.GetAIOwner()->GetPawn(); // get the AI pawn
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // get the player pawn
	if (AIPawn == nullptr || PlayerPawn == nullptr) //return if not found
	{
		return;
	}
	if (AIPawn->GetController()->LineOfSightTo(PlayerPawn) == true) // if the enemy sees the character
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation()); // set the key to the player pawns location
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); // if the player is not seen, clear the value
	}
}
