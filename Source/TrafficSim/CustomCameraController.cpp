// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "Road.h"
#include "StatisticsHUD.h"
#include "CustomCamera.h"
#include "CustomCameraController.h"
#include "TrafficSimGameMode.h"

//Called when a road is clicked
//Should be called by ARoad::OnClicked()
void ACustomCameraController::addClickedRoad(ARoad* clickedRoad, bool hasBeenClicked)
{
	if (!hasBeenClicked)
	{
		if (clickedRoads.empty())
		{
			//turn hud on
			AStatisticsHUD* HUD = Cast<AStatisticsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if (HUD) // if exist, change the value of number of cars
			{
				HUD->enableHUD();
			}

		}
		clickedRoads.insert(clickedRoad);
	}
	else
	{
		if (clickedRoads.find(clickedRoad) != clickedRoads.end())
		{
			if (clickedRoads.size() == 1)
			{
				//turn hud off
				AStatisticsHUD* HUD = Cast<AStatisticsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
				if (HUD) // if exist, change the value of number of cars
				{
					HUD->disableHUD(); 
				}
			}
			clickedRoads.erase(clickedRoad);
		}
	}
}

//Called when a road entry is clicked
//Should be called by ARoadEntry::OnClicked()
void ACustomCameraController::addClickedRoadEntry(ARoadEntry* inClickedEntry)
{
	//Unclick currently clicked entry
	if (clickedRoadEntry != nullptr)
	{
		clickedRoadEntry->setIsClicked(false);
	}

	if (clickedEntryWidget == nullptr)
	{
		clickedEntryWidget = CreateWidget<URoadEntryWidget>(GetWorld(), entryWidgetReference);
		roadEntryWidgetVisible = false;
	}

	clickedRoadEntry = inClickedEntry;
	if (clickedEntryWidget != nullptr)
	{
		clickedEntryWidget->setInstigator(clickedRoadEntry);
		clickedEntryWidget->loadValues();
	}

	if (!roadEntryWidgetVisible)
	{
		roadEntryWidgetVisible = true;
		clickedEntryWidget->AddToViewport();
		SetPause(true);
	}
}

void ACustomCameraController::removeClickedRoadEntry(ARoadEntry* inClickedEntry)
{
	SetPause(false);
	if (roadEntryWidgetVisible)
	{
		roadEntryWidgetVisible = false;
		clickedEntryWidget->RemoveFromViewport();
		clickedEntryWidget = nullptr;
	}
}

//Called by MyCar::OnClick
void ACustomCameraController::carClick(AMyCar* newClickedCar)
{
	if (clickedCar != nullptr)
	{
		clickedCar->setHasBeenClicked(false);
	}

	if (clickedCarWidget == nullptr)
	{
		clickedCarWidget = CreateWidget<UCarCameraWidget>(GetWorld(), carWidgetReference);
		bCarBeenClicked = false;
	}

	clickedCarWidget->setInstigator(newClickedCar);
	clickedCar = newClickedCar;
	Possess(clickedCar);

	if(!bCarBeenClicked)
	{
		clickedCarWidget->AddToViewport();
		bCarBeenClicked = true;
	}
}

void ACustomCameraController::carUnClick(AMyCar* newClickedCar)
{
	if (bCarBeenClicked)
	{
		clickedCarWidget->RemoveFromViewport();
		clickedCarWidget = nullptr;
		bCarBeenClicked = false;
	}
//newClickedCar->setHasBeenClicked(false);
	ATrafficSimGameMode* tempGameMode = (ATrafficSimGameMode*)GetWorld()->GetAuthGameMode();
	Possess(tempGameMode->getPlayer());
}

//Calculates the avg speed and profile ratios for statistics
void ACustomCameraController::calcAvgSpeedAndRatio()
{
	//Use temp variables then assign them at the end of the function
	int32 tRatioSafeDriver = 0;
	int32 tRatioNormalDriver = 0;
	int32 tRatioAggressiveDriver = 0;

	float tempSpeed = 0.f;
	int count = 0;

	//Iterate through clicked roads
	std::set<ARoad*>::iterator iter;
	for (iter = clickedRoads.begin(); iter != clickedRoads.end(); iter++)
	{
		(*iter)->calcAvgSpeedAndRatio();
		tempSpeed += (*iter)->getAvgSpeed();
		tRatioSafeDriver += (*iter)->getSafeTally();
		tRatioNormalDriver += (*iter)->getNormalTally();
		tRatioAggressiveDriver += (*iter)->getAggressiveTally();
		count++;
	}

	tempSpeed = tempSpeed / (float)count;

	ratioSafeDriver = tRatioSafeDriver;
	ratioNormalDriver = tRatioNormalDriver;
	ratioAggressiveDriver = tRatioAggressiveDriver;

	avgSpeed = tempSpeed;
}

//Gets the number of cars clicked. Mainly for statistics but can be used for other things
int32 ACustomCameraController::getAllClickedCarCount()
{
	int32 vehicles = 0;
	std::set<ARoad*>::iterator iter;
	for (iter = clickedRoads.begin(); iter != clickedRoads.end(); iter++)
	{
		vehicles += (*iter)->getVehicleCount();
	}

	return vehicles;
}

//Think I used this to set the Instigator for the widget
ARoadEntry* ACustomCameraController::getClickedRoadEntry()
{
	if (clickedRoadEntry == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("NULL POINTERRRR!!"));
	return clickedRoadEntry;
}

//Returns the prepared average speed value
float ACustomCameraController::getAllClickedSpeed()
{
	return avgSpeed;
}

//returns safe ratio driver profile ratio on selected roads
//need to call calcAvgSpeedAndRatio() before this is usefull
int32 ACustomCameraController::getSafeRatio()
{
	return ratioSafeDriver;
}

//returns normal ratio driver profile ratio on selected roads
//need to call calcAvgSpeedAndRatio() before this is usefull
int32 ACustomCameraController::getNormalRatio()
{
	return ratioNormalDriver;
}

//returns aggressive ratio driver profile ratio on selected roads
//need to call calcAvgSpeedAndRatio() before this is usefull
int32  ACustomCameraController::getAggressiveRatio()
{
	return ratioAggressiveDriver;
}