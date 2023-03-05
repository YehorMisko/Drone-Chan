// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

class APlayerCameraManager;
UCLASS()
class MYSHOOTER_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();
	/*Active the drone*/
	void Activate(ACharacter* Interactor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*Create a Collision Box*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		class UBoxComponent* CollisionBox;
	/*Create a Skeletal Mesh for the drone*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkeletalMesh)
		class USkeletalMeshComponent* SkeletalMesh;
	/*Create the floating pawn movement component for movement*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class UFloatingPawnMovement* PawnMovement;
	/*Create the camera that shows waht the drone sees using it's camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* DroneCam;
	/*Create a spot light for the drone to shine on near objects*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpotLightComponent* CamSpotLight;
	/*Creat a screen Widget for drone UI*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UWidgetComponent* DroneScreenWidget;


private:
	/*Check if the drone is possessed or not*/
	UPROPERTY()
		bool droneActivated;
	/*Movement functionality, simmiliar to the Character*/
	void MoveUp(float Value);
	void MoveRight(float Value);
	void MoveForward(float Value);
	void TurnRight(float Value);
	void LookUp(float Value);
	/*Deactivate the drone, return to the character*/
	void Deactivate();
	/*Controller of the Character*/
	AController* playerController;
	/*The character that possesed the drone*/
	ACharacter* player;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
