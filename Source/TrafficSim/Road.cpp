// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "Road.h"
#include "MyCar.h"
#include "CustomCameraController.h"

// Sets default values
ARoad::ARoad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//create objects
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("RoadZone"));
	myMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoadMesh"));
	directionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DirectionBox"));

	myMesh->bCastDynamicShadow = false;
	//set the static mesh to be the root component
	RootComponent = myMesh;

	//set a road static mesh to the object
	const ConstructorHelpers::FObjectFinder<UStaticMesh> roadMesh(TEXT("/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400"));
	myMesh->SetStaticMesh(roadMesh.Object);

	//set the material for the road
	const ConstructorHelpers::FObjectFinder<UMaterial> roadMaterial(TEXT("/Game/Asphalt01/Asphalt01_D_Mat.Asphalt01_D_Mat"));
	mat = roadMaterial.Object;
	const ConstructorHelpers::FObjectFinder<UMaterial> roadMaterialGlow(TEXT("/Game/Asphalt01/Asphalt01_D_Mat_Glow.Asphalt01_D_Mat_Glow"));
	matGlow = roadMaterialGlow.Object;
	myMesh->SetMaterial(0, mat);

	//attach the box to the static mesh
	box->AttachTo(RootComponent);
	directionBox->AttachTo(RootComponent);

	//initialize map size variable
	mapSize = 0;

	//set initial size of static mesh and location
	myMesh->SetRelativeLocation(FVector(100.f, 100.f, 100.f));

	//set initial size of box and location reletive to static mesh
	box->SetRelativeLocation(FVector(200.f, 200.f, 45.f));
	box->SetRelativeScale3D(FVector(6.25f, 6.25f, 1.5f));
	
	//Position the box for a deveopment visual on the direction of the road
	directionBox->SetRelativeLocation(FVector(400.f, 200.f, 45.f));
	directionBox->SetWorldScale3D(FVector(1.f, 6.25f, 1.5f));

	//Event when something enters the box
	box->OnComponentBeginOverlap.AddDynamic(this, &ARoad::enteredBox);

	//Event when something leaves the box
	box->OnComponentEndOverlap.AddDynamic(this, &ARoad::leftBox);

	//Initialize Max Driving Speed;
	maxDrivingSpeed = 100;

	hasBeenClicked = false;
	myMesh->OnClicked.AddDynamic(this, &ARoad::OnClick);

	//Iniatialize ratio statistics variables
	ratioSafe = 0;
	ratioNorm = 0;
	ratioAggressive = 0;
}

void ARoad::InitDirectionVector()
{
	directionVector = box->GetComponentRotation().GetInverse().Vector();
}

// Called when the game starts or when spawned
void ARoad::BeginPlay()
{
	Super::BeginPlay();

	//Initialize direction vector.
	InitDirectionVector();
}

// Called every frame
void ARoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Triggered when a car enters the box (box = collision box always set ontop of the road)
//void ARoad::enteredBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
void ARoad::enteredBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyCar * castedActor = dynamic_cast<AMyCar*>(OtherActor))
	{
		vehicleMap[castedActor->GetUniqueID()] = castedActor;
		mapSize++;
	}
}

//Triggered when a car leaves the box
//void ARoad::leftBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
void ARoad::leftBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AMyCar * castedActor = dynamic_cast<AMyCar*>(OtherActor))
	{
		vehicleMap.erase(OtherActor->GetUniqueID());
		mapSize--;
	}
}

//Triggered when the roads static mesh is clicked
void ARoad::OnClick(class UPrimitiveComponent* OtherComp, FKey inKey)
{
	//Could develop roads own controller class for future refactoring
	ACustomCameraController* con = (ACustomCameraController*)UGameplayStatics::GetPlayerController(GetWorld(), 0);
	con->addClickedRoad(this, hasBeenClicked);

	if (!hasBeenClicked)
	{
		myMesh->SetMaterial(0, matGlow);
		hasBeenClicked = true;
	}
	else
	{
		myMesh->SetMaterial(0, mat);
		hasBeenClicked = false;
	}
}

//This could also be done using the enter and leave events to improve performance
void ARoad::tallyCarTypes(int32 inType, int32* inRatioSafe, int32* inRatioNorm, int32* inRatioAggressive)
{
	switch (inType)
	{
		case 1: (*inRatioSafe)++;			break;
		case 2: (*inRatioNorm)++;			break;
		case 3: (*inRatioAggressive)++;		break;
	}
}

//Get the average speed of all cars on the road
void ARoad::calcAvgSpeedAndRatio()
{
	//Temp variables
	int32 tRatioSafe = 0;
	int32 tRatioNorm = 0;
	int32 tRatioAggressive = 0;

	AMyCar* tempCar;
	float tempSpeed = 0.f;
	std::map<uint32, AMyCar*>::iterator iter;
	for (iter = vehicleMap.begin(); iter != vehicleMap.end(); iter++)
	{
		tempCar = iter->second;
		tempSpeed += (float)tempCar->CalculateSpeed();
		tallyCarTypes(tempCar->getTypeOfCar(), &tRatioSafe, &tRatioNorm, &tRatioAggressive);
	}

	//Avoid divide by 0 error
	if(!vehicleMap.empty())
	{
		tempSpeed = tempSpeed / (float)mapSize;
	}
		avgSpeed = tempSpeed;

	ratioSafe = tRatioSafe;
	ratioNorm = tRatioNorm;
	ratioAggressive = tRatioAggressive;
}


float ARoad::getAvgSpeed()
{
	return avgSpeed;
}

//Get the vehicle count of all cars on the road
int32 ARoad::getVehicleCount()
{
	return mapSize;
}

int32 ARoad::getSafeTally()
{
	return ratioSafe;
}

int32 ARoad::getNormalTally()
{
	return ratioNorm;
}

int32 ARoad::getAggressiveTally()
{
	return ratioAggressive;
}