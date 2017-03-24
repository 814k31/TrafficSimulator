// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomCameraController.h"
#include "GameFramework/HUD.h"
#include "StatisticsHUD.generated.h"

/**
 * 
 */
UCLASS()
class TRAFFICSIM_API AStatisticsHUD : public AHUD
{
	GENERATED_BODY()
	
public: 
	AStatisticsHUD();

	//Font to use by the HUD
	UPROPERTY()
		UFont* HUDFont;

	//to draw the HUD
	virtual void DrawHUD() override;

	bool showHUD;
	void enableHUD();
	void disableHUD();

	//Get methods to convert values into FText for hud display
	FText getNumOfCar();
	FText getAvgSpeed();
	FText getProfRatio();

private:
	ACustomCameraController* camControl;

	//aveSpeed gets its own variable so the refresh rate can be slowed down - this is the purpose of the count variable
	int32 count;
	FText aveSpeed;
};

