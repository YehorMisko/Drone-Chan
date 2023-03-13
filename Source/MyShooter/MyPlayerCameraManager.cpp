// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPlayerCameraManager::AMyPlayerCameraManager()
{
	ViewPitchMax = 60.0f;
	ViewPitchMin = -80.0f;
	isOnDrone = false;
}
//If on drone clamp, if not unclamp
void AMyPlayerCameraManager::DroneClamp()
{
	isOnDrone = !isOnDrone;
	if (isOnDrone == true)
	{
		ViewPitchMax = 10.0f;
		ViewPitchMin = -80.0f;
	}
	else
	{
		ViewPitchMax = 60.0f;
		ViewPitchMin = -80.0f;
	}
	
}

