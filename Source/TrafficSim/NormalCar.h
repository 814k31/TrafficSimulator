// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCar.h"
#include "NormalCar.generated.h"

/**
 * 
 */
UCLASS()
class TRAFFICSIM_API ANormalCar : public AMyCar
{
	GENERATED_BODY()
	//Child Class of AMyCar
public:
	ANormalCar();
	
	virtual int32 getTypeOfCar() override;
};
