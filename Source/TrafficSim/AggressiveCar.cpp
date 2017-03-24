// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "AggressiveCar.h"

//Child Class of AMyCar
//Sets some basic custom functions
AAggressiveCar::AAggressiveCar()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material(TEXT("/Game/Vehicle/Sedan/Materials/M_Vehicle_Sedan_Inst_TailLights"));
	GetMesh()->SetMaterial(2, Material.Object);
	Vehicle4W->EngineSetup.MaxRPM = 8000.0f;
}

//3 is the designated number for aggressive cars
int32 AAggressiveCar::getTypeOfCar()
{
	return 3;
}