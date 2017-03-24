// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCar.h"
#include "SafeCar.generated.h"

/**
 * 
 */
UCLASS()
class TRAFFICSIM_API ASafeCar : public AMyCar
{
	GENERATED_BODY()

public:
	ASafeCar();

	virtual int32 getTypeOfCar() override;
};
