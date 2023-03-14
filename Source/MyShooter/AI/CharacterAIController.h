// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYSHOOTER_API ACharacterAIController : public AAIController
{
	GENERATED_BODY()
protected:
	//Sets the defaults
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	//The tree that will be used
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior;
	
};
