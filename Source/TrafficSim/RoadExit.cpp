// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "CustomCameraController.h"
#include "RoadExit.h"


// Sets default values
ARoadExit::ARoadExit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	exitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ExitBox"));
	exitBox->AttachTo(RootComponent);

	exitBox->SetRelativeScale3D(FVector(1.f, 6.25f, 1.5f));
	exitBox->SetRelativeLocation(FVector(32.f, 200.f, 45.f));

	//Event when something enters the box
	directionBox->OnComponentBeginOverlap.AddDynamic(this, &ARoadExit::killCar);
}

// Called when the game starts or when spawned
void ARoadExit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoadExit::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
}

//Destroys all the  cars that hit the end of the road
//Only destroys cars
void ARoadExit::killCar(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCar* enteredCar = Cast<AMyCar>(OtherActor);

	if (enteredCar != nullptr)
	{
		//If the car is clicked go back to default pawn
		if (enteredCar->getHasBeenClicked())
		{
			ACustomCameraController* camController = (ACustomCameraController*)GetWorld()->GetFirstPlayerController();
			camController->carUnClick(enteredCar);
		}
		enteredCar->Destroy();
	}
}

void ARoadExit::OnClick(class UPrimitiveComponent* OtherComp)
{
	//No implementation when a road exit is clicked
}