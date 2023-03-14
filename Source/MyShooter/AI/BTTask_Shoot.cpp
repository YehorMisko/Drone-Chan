// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "../Player/MyShooterCharacter.h"
//sets the default values
UBTTask_Shoot::UBTTask_Shoot()
{
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr) //if no owner fail the task
    {
        return EBTNodeResult::Failed;
    }
    AICharacter = Cast<AMyShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn()); // get the pawn
    if (AICharacter == nullptr) //fail if pawn not found
    {
        return EBTNodeResult::Failed; 
    }
    AICharacter->FireWeapon(); // pawn fires the weapon
    return EBTNodeResult::Succeeded;
}
