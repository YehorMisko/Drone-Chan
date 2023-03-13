// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"



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
	/*Custom Overlap function override*/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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
	/*Function for destroying the drone*/
	void Death();
	/*Particle system for the explosion*/
	UPROPERTY(EditDefaultsOnly, Category = ExplosionEffect)
	class UParticleSystem* ExplosionEffect;
	//Create a CameraManager for clamping the view
	APlayerCameraManager* Cam;
	/*Amount of health*/
	float health;
	/*Amount of starting health*/
	UPROPERTY(EditAnywhere)
	float maxHealth;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Called when damage is taken
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
};
