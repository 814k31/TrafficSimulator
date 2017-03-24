// Edited by Yvonne @ April 2016.
// Pawn type Car

#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "MyCar.generated.h"


class UPhysicalMaterial;

UCLASS()
class AMyCar : public AWheeledVehicle
{
	GENERATED_BODY()

		//Default Class for Car objects - Please construct child classes for full functionality
		//Child classes: SafeCar.h NormalCar.h AggressiveCar.h

public:
	// Sets default values for this pawn's properties
	AMyCar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


/******************************* Added code and functions :) *********************************************/
	int32 CalculateSpeed();
	void DisplaySpeed(); //temp
	void CalculateDistance(float Delta);

	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		FText DistDisplayString;

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* InCarSpeed;

	/** The current speed as a string eg 10 km/h */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		FText SpeedDisplayString;

	//Update the physics material used by the vehicle mesh
	void UpdatePhysicsMaterial();

	void SetupMovement();
	void SetupCamera();
	UCameraComponent* getCam();
	//Override onclick function so that the road entry can be customised to call a parameter widget
	UFUNCTION()
		void OnClick(class UPrimitiveComponent* OtherComp, FKey inKey);

	UFUNCTION(BlueprintCallable, Category = Car)
		void OnClickFunctionality();

	void setHasBeenClicked(bool newBeenClicked);
	bool getHasBeenClicked();
	virtual int32 getTypeOfCar();

protected:
	const float MoveValue = 1.f;
	const int SpeedLimit = 50;

	float distanceTraveled;
	void ChangeToRight();
	void PressBrakes();
	void ReleaseBrakes();
	void Drive(float Value);
	void Steering(float Value);
	void SetDirection(FVector newDirection);

	//Slippery Material?
	bool bIsLowFriction;
	//Slippery Material Instance
	UPhysicalMaterial* SlipperyMaterial;
	//Non Slippery Material Instance
	UPhysicalMaterial* NonSlipperyMaterial;

	UWheeledVehicleMovementComponent4W* Vehicle4W;
	FVector direction;

	USpringArmComponent* SpringArm;
	UCameraComponent* Camera;

	bool hasBeenClicked;
};
