// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include <GameFramework/DefaultPawn.h>
#include "GameFramework/Character.h"
#include "MyShooterCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MyPlayerCameraManager.h"
// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/*Create the collision box and set it as the root component*/
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Boxa Collision"));
	SetRootComponent(CollisionBox);
	/*Create the Sekeletal Mesh Component, attach to the root component*/
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletala Mesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	/*Create a Camera and attach it to the root component*/
	DroneCam = CreateDefaultSubobject<UCameraComponent>(TEXT("CamComponenta"));
	DroneCam->SetupAttachment(GetRootComponent());

	/*Create a spotlight and attach it to the camera*/
	CamSpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotaLighta"));
	CamSpotLight->SetupAttachment(DroneCam);
	/*Create the UI widget for the drone*/
	DroneScreenWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Drone Screen Widget"));
	/*Create the floating movement component and configure it to better replicate how a real life drone would behave*/
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Drone Float Movement"));
	PawnMovement->Acceleration = 8000.0f;
	PawnMovement->Deceleration = 500.0f;
	PawnMovement->TurningBoost = 1.0f;
	PawnMovement->MaxSpeed = 1200.0f;
	this->bUseControllerRotationYaw = true;
	/*By default the drone is not possesed*/
	droneActivated = false;
	
	/*By default health is set to 20*/
	maxHealth = 20.0f;
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	//Add the overriden BeginOverlap
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADrone::OnOverlapBegin);
	health = maxHealth;
	
}
//Runs when the drone is activated
void ADrone::Activate(ACharacter* Interactor)
{
	player = Interactor;
	droneActivated = !droneActivated;
	playerController = Interactor->GetController();
	playerController->Possess(this);
	UE_LOG(LogTemp, Warning, TEXT("Drone has been possesed"));
	//Get the CameraManager
	Cam = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	Cast<AMyPlayerCameraManager>(Cam)->DroneClamp();//Activate the clamp
}



void ADrone::MoveUp(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f)) {
		//find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw ,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Z) };
		PawnMovement->AddInputVector(Direction * Value);
		
	}
}

void ADrone::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f)) {
		//find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw ,0 };
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		PawnMovement->AddInputVector(Direction * Value);
	}
}

void ADrone::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f)) {
		//find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw ,0 };
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		PawnMovement->AddInputVector(Direction * Value);
	}
}
//Unused
void ADrone::TurnRight(float Value)
{
	AddControllerYawInput(Value * 45.0f * GetWorld()->GetDeltaSeconds());
}

/*Possess the character*/
void ADrone::Deactivate()
{
	Cast<AMyPlayerCameraManager>(Cam)->DroneClamp(); //Unclamp the cam
	droneActivated = !droneActivated;
    playerController->Possess(player);

	
}

void ADrone::Death()	
{
	const USkeletalMeshSocket* ExplosionSocket = SkeletalMesh->GetSocketByName("ExplosionSocket");
	if (ExplosionSocket)
	{
		if(Controller != nullptr) Cast<AMyPlayerCameraManager>(Cam)->DroneClamp(); //Unclamp the cam
		const FTransform SocketTransform = ExplosionSocket->GetSocketTransform(SkeletalMesh);
		playerController->Possess(player);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, SocketTransform);
		Destroy();	
	}
}

void ADrone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//If the obstacle is hit, destroy the drone
		if (OtherComp->GetName() == "ObstacleMesh")
		{
			Death();
		}
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

float ADrone::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	damageToApply = FMath::Min(health, damageToApply);
	health -= damageToApply;
	//Call the death func if health reaches 0
	if (health <= 0)Death();
	//UE_LOG(LogTemp, Warning, TEXT("Health left %f"), health);

	return damageToApply;
}


// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("FlyUp", this, &ADrone::MoveUp);
	PlayerInputComponent->BindAxis("MoveForward", this, &ADrone::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADrone::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &ADrone::TurnRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("DroneToggle", IE_Pressed, this, &ADrone::Deactivate);
	PlayerInputComponent->BindAction("TestAction", IE_Pressed, this, &ADrone::Death);
}

