// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "RoadEntry.h"
#include "CustomCameraController.h"
#include "MyCar.h"
#include "SafeCar.h"
#include "NormalCar.h"
#include "AggressiveCar.h"
#include "VehicleAIController.h"
#include <cstdlib>
#include <ctime>

ARoadEntry::ARoadEntry()
{
	//Enables tick function
	PrimaryActorTick.bCanEverTick = true;

	//Construct SpawnBox
	spawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	spawnBox->AttachTo(RootComponent);

	//Position SpawnBox
	spawnBox->SetRelativeLocation(FVector(200.f, 200.f, 45.f));

	//Set custom selected colour
	const ConstructorHelpers::FObjectFinder<UMaterial> roadMaterialGlow(TEXT("/Game/Asphalt01/Asphalt01_D_Mat_Glow_Yellow.Asphalt01_D_Mat_Glow_Yellow"));
	matGlow = roadMaterialGlow.Object;

	//Initialize spawn variables
	spawnRate = 500;
	spawnTime = 0;

	//ratios done in a percentage
	ratioSafe = 33;
	ratioNormal = 34;
	ratioAggressive = 33;

	defaultRatioSafe = 33;
	defaultRatioNormal = 34;
	defaultRatioAggressive = 33;
	defaultSpawnRate = 500;
	
	canSpawn = true;
}

//Tick function used to spawn cars 
void ARoadEntry::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (spawnTime >= spawnRate)
	{
		if (canSpawn)
		{
			FActorSpawnParameters params;
			params.Instigator = NULL;
			params.Owner = this;
			params.bNoCollisionFail = true;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

			AMyCar* spawnedVehicle = NULL;
			int32 randomNumber;
			int32 max = ratioSafe + ratioNormal + ratioAggressive;
			std::srand(std::time(0));

			randomNumber = std::rand() % 100 + 1;//(int32) FMath::RandRange(1.0f, 100.f);
//			randomNumber = randomNumber % 100000 + 1;
//			randomNumber = randomNumber % 10000 + 1;
//			randomNumber = randomNumber % 100 + 1;
//			randomNumber = randomNumber % max + 1;

UE_LOG(LogTemp, Warning, TEXT("Random Value %d"), randomNumber);


			//spawn object - need to check if location is free
			if ((randomNumber > 0) && (randomNumber <= ratioSafe))
			{
				spawnedVehicle = GetWorld()->SpawnActor<ASafeCar>(spawnBox->GetComponentLocation(), GetActorRotation().GetInverse(), params);
			}
			else if ((randomNumber > ratioSafe) && (randomNumber <= (ratioSafe + ratioNormal)))
			{
				spawnedVehicle = GetWorld()->SpawnActor<ANormalCar>(spawnBox->GetComponentLocation(), GetActorRotation().GetInverse(), params);
			}
			else if ((randomNumber > ratioNormal) && (randomNumber <= max))
			{
				spawnedVehicle = GetWorld()->SpawnActor<AAggressiveCar>(spawnBox->GetComponentLocation(), GetActorRotation().GetInverse(), params);
			}

			if (spawnedVehicle != NULL)
			{
				spawnedVehicle->SpawnDefaultController();
			}
				canSpawn = false;
		}
		//Reset Spawn Time
		spawnTime = 0;
	}
	spawnTime++;
}

//Triggers spawnable boolean variable
//void ARoadEntry::leftBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
void ARoadEntry::leftBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Super::leftBox(OtherActor, OtherComp, OtherBodyIndex);
	canSpawn = true;
}

//Click method called the the static mesh is clicked
//This method is overriden from superclass (ARoad)
void ARoadEntry::OnClick(class UPrimitiveComponent* OtherComp)
{
	OnClickFunctionality();
}

void ARoadEntry::OnClickFunctionality()
{
	ACustomCameraController* con = (ACustomCameraController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!hasBeenClicked)
	{
		con->addClickedRoadEntry(this);
		hasBeenClicked = true;
		myMesh->SetMaterial(0, matGlow);

	}
	else
	{
		con->removeClickedRoadEntry(this);
		hasBeenClicked = false;
		myMesh->SetMaterial(0, mat);
	}
}

//Gets hasbeenclicked value for error checking (used in roadentrywidget.cpp
bool ARoadEntry::getIsClicked()
{
	return hasBeenClicked;
}

//sets hasbeenclicked value for error prevention (used in roadentrywidget.cpp
void ARoadEntry::setIsClicked(bool newBeenClicked)
{
	hasBeenClicked = newBeenClicked;
	if (newBeenClicked)
	{
		myMesh->SetMaterial(0, matGlow);
	}
	else
	{
		myMesh->SetMaterial(0, mat);
	}
}

//Set and Get Methods for parameter editing
int32 ARoadEntry::getSpawnRate()
{
	return spawnRate / 100;
}

int32 ARoadEntry::getRatioSafe()
{
	return ratioSafe;
}

int32 ARoadEntry::getRatioNormal()
{
	return ratioNormal;
}

int32 ARoadEntry::getRatioAggressive()
{
	return ratioAggressive;
}

//Defaults for default button
int32 ARoadEntry::getDefaultRatioSafe()
{
	return defaultRatioSafe;
}

int32 ARoadEntry::getDefaultRatioNormal()
{
	return defaultRatioNormal;
}

int32 ARoadEntry::getDefaultRatioAggressive()
{
	return defaultRatioAggressive;
}

int32 ARoadEntry::getDefaultSpawnRate()
{
	return defaultSpawnRate / 100;
}

//Minimum spawn rate has to be set to one.
//I cannot find a suitable ue4 function that will
//perfectly check if there is any cars in the way of spawn
void ARoadEntry::setSpawnRate(int32 inSpawnRate)
{
	if (inSpawnRate > 0)
	{
		spawnRate = inSpawnRate * 100;
	}
	else if (inSpawnRate == 0)
	{
		spawnRate = 50;
	}
}

void ARoadEntry::setRatioSafe(int32 inRatioSafe)
{
	if (inRatioSafe >= 0)
	{
		ratioSafe = inRatioSafe;
	}
}
void ARoadEntry::setRatioNormal(int32 inRatioNormal)
{
	if (inRatioNormal >= 0)
	{
		ratioNormal = inRatioNormal;
	}
}
void ARoadEntry::setRatioAggressive(int32 inRatioAggressive)
{
	if (inRatioAggressive >= 0)
	{
		ratioAggressive = inRatioAggressive;
	}
}