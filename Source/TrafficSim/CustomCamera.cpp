// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "CustomCamera.h"
#include "Vehicles/WheeledVehicleMovementComponent4W.h"
#include "CustomCameraController.h"
#include "GameFramework/PlayerInput.h"

//This is the default pawn set to move around this world

// Sets default values
ACustomCamera::ACustomCamera()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera1"));
	cam->FieldOfView = 90.f;
	cam->AttachParent = RootComponent;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
	
	cam->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ACustomCamera::BeginPlay()
{
	Super::BeginPlay();
	//Enable the camera to move when the game is pause
	SetTickableWhenPaused(true);
}

// Called every frame
void ACustomCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void ACustomCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAction("ChangeController", IE_Pressed, this, &ACustomCamera::ChangeController);

	InputComponent->BindAxis("MoveForward", this, &ACustomCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACustomCamera::MoveRight);
	InputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ACustomCamera::LookUp);
	
	//allow action to work even when program is pause
	//InputComponent->BindAction("ChangeController", IE_Pressed, this, &ACustomCamera::ChangeController);

//	InputComponent->BindAxis("MoveForward", this, &ACustomCamera::MoveForward).bExecuteWhenPaused = true;
//	InputComponent->BindAxis("MoveRight", this, &ACustomCamera::MoveRight).bExecuteWhenPaused = true;
//	InputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput).bExecuteWhenPaused = true;
//	InputComponent->BindAxis("LookUp", this, &ACustomCamera::LookUp).bExecuteWhenPaused = true;

	//Super::SetupPlayerInputComponent(InputComponent);

}

void ACustomCamera::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACustomCamera::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACustomCamera::LookUp(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Add movement in that direction
		AddControllerPitchInput((Value * -1.f));
	}
}

//Seems to be disabled
void ACustomCamera::ChangeController()
{
	APlayerController* control = (APlayerController*)GetController();
	if (control->bShowMouseCursor == true)
	{
		control->bShowMouseCursor = false;
	}
	else
	{
		control->bShowMouseCursor = true;
	}
}