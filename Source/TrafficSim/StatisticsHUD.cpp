// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "StatisticsHUD.h"
#include "CanvasItem.h"
#include "Engine/Font.h"
#include "Engine/Canvas.h"

#define LOCTEXT_NAMESPACE "StatsHud"

AStatisticsHUD::AStatisticsHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
	showHUD = false; // initialize it false to hide the HUD
	count = 0;
	aveSpeed = FText::FromString(FString(TEXT("0")));
}

void AStatisticsHUD::DrawHUD()
{
	//Only display hud when showHUD is positive
	if (showHUD)
	{
		//This function is called in loop untill the program stops
		Super::DrawHUD();
		//To make it in resolution of 720p
		const float HUDXRatio = Canvas->SizeX / 1280.f;
		const float HUDYRatio = Canvas->SizeY / 720.f;

		camControl->calcAvgSpeedAndRatio();

		//Reduce Refresh Ratio of average speed.
		count++;
		if (count > 25)
		{
			aveSpeed = getAvgSpeed();
			count = 0;
		}

		//Test files only to fill the canvas
		FText labelNumberOfCars = FText::Format(LOCTEXT("NumberOfCars", "Number of Cars: {0}"), getNumOfCar());
		FText labelAveSpeed = FText::Format(LOCTEXT("AveSpeedPerLane", "Average speed: {0}"), aveSpeed);
		FText labelDriverProfileRatio = FText::Format(LOCTEXT("DriverRatio", "Driver Profile Ratio: {0}"), getProfRatio());

		FVector2D ScaleVec(HUDYRatio * 1.4f, HUDYRatio * 1.4f);
		//Position of the HUD
		FCanvasTextItem canvasNumberOfCars(FVector2D(HUDXRatio * 70.f, HUDYRatio * 455), labelNumberOfCars, HUDFont, FLinearColor::Black);
		canvasNumberOfCars.Scale = ScaleVec;
	
		FCanvasTextItem canvasAverageSpeed(FVector2D(HUDXRatio * 70.f, HUDYRatio * 505), labelAveSpeed, HUDFont, FLinearColor::Black);
		canvasAverageSpeed.Scale = ScaleVec;
	
		FCanvasTextItem canvasProfileRatio(FVector2D(HUDXRatio * 70.f, HUDYRatio * 555), labelDriverProfileRatio, HUDFont, FLinearColor::Black);
		canvasProfileRatio.Scale = ScaleVec;
	
		Canvas->DrawItem(canvasNumberOfCars);
		Canvas->DrawItem(canvasAverageSpeed);
		Canvas->DrawItem(canvasProfileRatio);
	}
}
//To enable and disable HUD
void AStatisticsHUD::enableHUD()
{
	showHUD = true;
	//Need to add downcast error checking
	camControl = (ACustomCameraController*)GetOwningPlayerController();
}

//Disables the hud shown when atleast one road is selected
void AStatisticsHUD::disableHUD()
{
	showHUD = false;
}

//The functions is to change the value showing into the screen
FText AStatisticsHUD::getNumOfCar()
{
	FText text;
	if (camControl != NULL)
	{
		text = FText::AsNumber(camControl->getAllClickedCarCount());
	}
	else
	{
		text = FText::FromString(TEXT("0"));
	}
	return text;
}

//Gets average speed from controller and converts it to FText
FText AStatisticsHUD::getAvgSpeed()
{
	FText text;
	if (camControl != NULL)
	{
		text = FText::AsNumber(std::floor(camControl->getAllClickedSpeed()));
	}
	return text;
}

//Gets driver profile ratio from controller and converts it to FText
FText AStatisticsHUD::getProfRatio()
{
	FText concatString;
	FText safeRatio;
	FText normalRatio;
	FText aggressiveRatio;

	if (camControl != NULL)
	{
		//avoid 0/0 exception
		if (camControl->getAllClickedCarCount() > 0)
		{
			safeRatio = FText::AsNumber((camControl->getSafeRatio() * 100 / camControl->getAllClickedCarCount()));
			normalRatio = FText::AsNumber((camControl->getNormalRatio() * 100 / camControl->getAllClickedCarCount()));
			aggressiveRatio = FText::AsNumber((camControl->getAggressiveRatio() * 100 / camControl->getAllClickedCarCount()));
		}
		else
		{
			safeRatio = FText::AsNumber(0);
			normalRatio = FText::AsNumber(0);
			aggressiveRatio = FText::AsNumber(0);
		}
	}
	concatString = FText::Format(LOCTEXT("DriverRatio", "Safe: {0}% Normal: {1}% Aggressive: {2}%"), safeRatio, normalRatio, aggressiveRatio);
	return concatString;
}
 