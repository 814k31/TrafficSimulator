// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "VehicleAIController.generated.h"

/**
//Vehicle AIController - Created when attempting to implement AI
//Vehicle currently has APlayerController set to drive forward
 */
UCLASS()
class TRAFFICSIM_API AVehicleAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AVehicleAIController(const FObjectInitializer& ObjectInitializer);
};
