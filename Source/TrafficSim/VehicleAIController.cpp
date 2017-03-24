// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "VehicleAIController.h"
#include "VehiclePathFollowingComponent.h"

//Vehicle AIController - Created when attempting to implement AI
//Vehicle currently has APlayerController set to drive forward

AVehicleAIController::AVehicleAIController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UVehiclePathFollowingComponent>(TEXT("PathFollowingComponent")))
{

}