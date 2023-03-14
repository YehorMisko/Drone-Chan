// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PLayerLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTER_API UBTService_PLayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	//sets the default values
	UBTService_PLayerLocationIfSeen();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override; //tick func override

private:
	class APawn* PlayerPawn; // the player pawn
	class APawn* AIPawn; // the AI pawn
};
