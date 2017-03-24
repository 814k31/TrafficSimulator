// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCar.h"
#include "AggressiveCar.generated.h"

/**
 * 
 */
UCLASS()
class TRAFFICSIM_API AAggressiveCar : public AMyCar
{
	GENERATED_BODY()
	
public:
	AAggressiveCar();
	//Override parent class function	
	virtual int32 getTypeOfCar() override;

	//Add more in here when developing AI and aggressive driver specifics
};
