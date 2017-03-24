// Edited by Yvonne @ April 2016 for Traffic Simulation Project Semester 1.

#include "TrafficSim.h"
#include "MyCar.h"
#include "TrafficSimWheelFront.h"
#include "TrafficSimWheelRear.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "VehiclePathFollowingComponent.h"
#include "VehicleAIController.h"
#include "CustomCameraController.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

// Constructor - Sets default values for each Car instance
AMyCar::AMyCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create materials for car colour behaviours
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CarSkeletalMesh(TEXT("/Game/Vehicle/Sedan/Sedan_SkelMesh.Sedan_SkelMesh"));

	//Setup friction materials
//	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> SlipperyMat(TEXT("/Game/VehicleAdv/PhysicsMaterials/Slippery.Slippery"));
//	SlipperyMaterial = SlipperyMat.Object;

//	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> NonSlipperyMat(TEXT("/Game/VehicleAdv/PhysicsMaterials/NonSlippery.NonSlippery"));
//	NonSlipperyMaterial = NonSlipperyMat.Object;

	if (CarSkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CarSkeletalMesh.Object);
		GetMesh()->OnClicked.AddDynamic(this, &AMyCar::OnClick);
	}

	// added a onscreen text component to test values; Create text render component for in car speed display
	InCarSpeed = CreateDefaultSubobject<UTextRenderComponent>(TEXT("InCarSpeed"));
	InCarSpeed->SetRelativeLocation(FVector(0.0f, -75.0f, 150.0f));
	InCarSpeed->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	InCarSpeed->AttachTo(GetMesh());
	InCarSpeed->SetWorldSize(50.f);

	bIsLowFriction = false;

	SetupMovement();
	SetupCamera();

	hasBeenClicked = false;


	/*For use when AI is being developped*/
	//AutoPossessPlayer = EAutoReceiveInput::Disabled;
	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	//AIControllerClass = AVehicleAIController::StaticClass();	
}

void AMyCar::SetupMovement()
{
	/* Imported from Vehicle project for simulation */
	Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	//Set inertia scale. Controls the vehicles mass distribution
	Vehicle4W->InertiaTensorScale = FVector(1.0f, 1.333f, 1.2f);

	check(Vehicle4W->WheelSetups.Num() == 4);

	Vehicle4W->WheelSetups[0].WheelClass = UTrafficSimWheelFront::StaticClass();
	Vehicle4W->WheelSetups[0].BoneName = FName("Wheel_Front_Left");
	Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = UTrafficSimWheelFront::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("Wheel_Front_Right");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	Vehicle4W->WheelSetups[2].WheelClass = UTrafficSimWheelRear::StaticClass();
	Vehicle4W->WheelSetups[2].BoneName = FName("Wheel_Rear_Left");
	Vehicle4W->WheelSetups[2].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	Vehicle4W->WheelSetups[3].WheelClass = UTrafficSimWheelRear::StaticClass();
	Vehicle4W->WheelSetups[3].BoneName = FName("Wheel_Rear_Right");
	Vehicle4W->WheelSetups[3].AdditionalOffset = FVector(0.f, 12.f, 0.f);

}

void AMyCar::SetupCamera()
{
	//Connects Camera to car
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->AttachTo(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 7.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;
}


// Called when the game starts or when spawned
void AMyCar::BeginPlay()
{
	Super::BeginPlay();
	direction = GetActorForwardVector();

	//To make the car drive forward
	//Remove this when developing AI
	Drive(MoveValue);
}

// Called every frame
void AMyCar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//Update physics material
	UpdatePhysicsMaterial();
	
	CalculateSpeed();
	DisplaySpeed();
}

// Called to bind functionality to input
void AMyCar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AMyCar::Drive(float Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value);
}
 
void AMyCar::Steering(float Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void AMyCar::SetDirection(FVector newDirection)
{
	direction = newDirection;
}

int32 AMyCar::CalculateSpeed()
{
	float KPH = FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) * 0.036f;
	int32 KPH_int = FMath::FloorToInt(KPH);

	// Using FText because this is display text that should be localizable
	SpeedDisplayString = FText::Format(LOCTEXT("SpeedFormat", "{0} km/h"), FText::AsNumber(KPH_int));
	return KPH_int;
}

void AMyCar::DisplaySpeed()
{
	// Setup the text render component strings
	InCarSpeed->SetText(SpeedDisplayString);
}

void AMyCar::CalculateDistance(float Delta)
{
	float speed = FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) * 0.036f; // km/hr
	distanceTraveled += ((speed/60.f)/60.f)*1000 * Delta;
	int32 distanceTraveled_int = FMath::FloorToInt(distanceTraveled);

	DistDisplayString = FText::Format(LOCTEXT("DistanceFormat", "{0} metres"), FText::AsNumber(distanceTraveled));
}

int32 AMyCar::getTypeOfCar()
{
	return 0;
}

void AMyCar::PressBrakes()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AMyCar::ReleaseBrakes()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AMyCar::UpdatePhysicsMaterial()
{
	if (GetActorUpVector().Z < 0)
	{
		if (bIsLowFriction == true)
		{
			GetMesh()->SetPhysMaterialOverride(NonSlipperyMaterial);
			bIsLowFriction = false;
		}
		else
		{
			GetMesh()->SetPhysMaterialOverride(SlipperyMaterial);
			bIsLowFriction = true;
		}
	}
}

//Triggered when a car is clicked
//Possesses the car
void AMyCar::OnClick(class UPrimitiveComponent* OtherComp, FKey inKey)
{
	OnClickFunctionality();
}

void AMyCar::OnClickFunctionality()
{
	ACustomCameraController* camController = (ACustomCameraController*)GetWorld()->GetFirstPlayerController();

	if (!hasBeenClicked)
	{
		camController->carClick(this);
		hasBeenClicked = true;
	}
	else
	{
		camController->carUnClick(this);
		hasBeenClicked = false;
	}
}

UCameraComponent* AMyCar::getCam()
{
	return Camera;
}

bool AMyCar::getHasBeenClicked()
{
	return hasBeenClicked;
}

void AMyCar::setHasBeenClicked(bool newBeenClicked)
{
	hasBeenClicked = newBeenClicked;
}
#undef LOCTEXT_NAMESPACE