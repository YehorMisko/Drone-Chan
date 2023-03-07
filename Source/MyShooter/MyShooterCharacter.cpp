// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include"Gun.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include"DrawDebugHelpers.h"
#include "Drone.h"


// Sets default values
AMyShooterCharacter::AMyShooterCharacter():
	BaseTurnRate(45.f),
	BaseLookUpRate(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the character if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f; //The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	// Create a Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach camera to end of boom
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//By default drone is not possessed
	isOnDrone = false;
	//By Default you get 3 drones
	DroneAmmo = 3;
}

// Called when the game starts or when spawned
void AMyShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*Spawn a Gun in the world and attach it to the character, to do: create a system where the character can pick up weapons*/
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	
	/*Spawn a Drone in the world*/
	

}
void AMyShooterCharacter::Test()
{
	/*Test if an action is working*/
	UE_LOG(LogTemp, Warning, TEXT("Action"));
}

void AMyShooterCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f)) {
		//find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw ,0};

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X)};
		AddMovementInput(Direction, Value);
	}
}

void AMyShooterCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f)) {
		//find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw ,0 };

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);
	}
}

void AMyShooterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); // deg/sec * sec/frame
	
}

void AMyShooterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds()); //deg/sec * sec/frame
	
}
/*WIP*/
bool AMyShooterCharacter::TraceUnderCrosshairs(FHitResult& OutHitResult)
{
	
	FVector2D ViewPortSize;
	if (GEngine && GEngine->GameViewport)
	{
		//GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
	return false;

}
/*WIP*/
void AMyShooterCharacter::FireWeapon()
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire Weapon"));

	const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("BarrelMuzzle");
	if (BarrelSocket)
	{
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh());
		/*Spawn an Emitter at muzzle socket*/
		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);
		}

		FHitResult FireHit;
		const FVector Start{ SocketTransform.GetLocation() };

		const FQuat Rotation{ SocketTransform.GetRotation() };

		const FVector RotationAxis{ Rotation.GetAxisX() };

		const FVector End{ Start + RotationAxis * 50'000.f };
		/*Line Trace by Channel and draw a debug line for a visual representation of the shot*/
		GetWorld()->LineTraceSingleByChannel(FireHit, Start, End, ECollisionChannel::ECC_Visibility);
		
		if (FireHit.bBlockingHit)
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);
			DrawDebugPoint(GetWorld(), FireHit.Location, 5.f, FColor::Red, false, 2.f);
		}
		
	}
}

void AMyShooterCharacter::ToggleDrone()
{
	
	/*Possess the drone*/
	if (IsValid(Drone)) {
		Drone->Activate(Cast<ACharacter>(this));
	}
	else if(DroneAmmo > 0){
		DroneAmmo--;
		Drone = GetWorld()->SpawnActor<ADrone>(DroneClass,GetActorLocation(),GetActorRotation());
		Drone->Activate(Cast<ACharacter>(this));
		
	}

}

void AMyShooterCharacter::AxisTest(float Value)
{
	/*Test if an axis is working*/
	UE_LOG(LogTemp, Warning, TEXT("Axis"));
}

// Called every frame
void AMyShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
		PlayerInputComponent->BindAxis("MoveForward", this, &AMyShooterCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AMyShooterCharacter::MoveRight);
		PlayerInputComponent->BindAxis("TurnRate", this, &AMyShooterCharacter::TurnAtRate);
		PlayerInputComponent->BindAxis("TurnUpRate", this, &AMyShooterCharacter::LookUpAtRate);
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
		PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
		PlayerInputComponent->BindAction("FireButton", IE_Pressed, this, &AMyShooterCharacter::FireWeapon);
	    PlayerInputComponent->BindAction("DroneToggle", IE_Pressed, this, &AMyShooterCharacter::ToggleDrone);
}

