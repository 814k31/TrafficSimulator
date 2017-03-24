// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "CustomCamera.generated.h"

UCLASS()
class ACustomCamera : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Function to toggle show mouse cursor - called when user pressed 'c'
	UFUNCTION()
		void ChangeController();

	UFUNCTION()
		void MoveForward(float val);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void LookUp(float Value);

	UPROPERTY(EditAnywhere)
		UCameraComponent* cam;
};
