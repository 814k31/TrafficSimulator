// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "SafeCar.h"

//Child class of AMyCar
ASafeCar::ASafeCar()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material(TEXT("/Game/Vehicle/Meshes/WhiteMaterial"));
	GetMesh()->SetMaterial(2, Material.Object);
	Vehicle4W->EngineSetup.MaxRPM = 5000.0f;
}

//Safe car ID is 1
int32 ASafeCar::getTypeOfCar()
{
	return 1;
}