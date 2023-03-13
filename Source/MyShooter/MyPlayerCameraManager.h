// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "MyPlayerCameraManager.generated.h"

/**
 * 
 */

UCLASS()
class MYSHOOTER_API AMyPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AMyPlayerCameraManager();

	// change the clamp values for the drone
	void DroneClamp();
private:
	//Check if in on drone
	bool isOnDrone;
};
