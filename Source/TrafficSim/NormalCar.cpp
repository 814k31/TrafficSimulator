// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "NormalCar.h"

//Child Class of AMyCar
//Sets some basic custom functions
ANormalCar::ANormalCar()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material(TEXT("/Game/Vehicle/Sedan/Materials/M_Vehicle_Sedan_Inst_Paint"));
	GetMesh()->SetMaterial(2, Material.Object);
	Vehicle4W->EngineSetup.MaxRPM = 6000.0f;
}

int32 ANormalCar::getTypeOfCar()
{
	return 2;
}