// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "MyCar.h"
#include "TrafficSimGameMode.h"
#include "CarCameraWidget.generated.h"

/**
 * 
 */
UCLASS()
//Widget displayed when a car is clicked
//Super class for blueprint class "CarWidget"
//Located in Content/Widget/
class TRAFFICSIM_API UCarCameraWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// function to be call by blueprint
	UFUNCTION(BlueprintCallable, Category = "Car Camera")
		void closeCamera();

	void setInstigator(AMyCar* newCar);
	UFUNCTION(BlueprintCallable, Category = "Car Camera")
		AMyCar* getInstigator();

protected:
	AMyCar* instigator;
	
};
