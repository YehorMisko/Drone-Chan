// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTER_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
public:
	//sets the default values
	UBTTask_Shoot();
protected:
	//override for the execute task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	//The AI Character
	class AMyShooterCharacter* AICharacter;
};
