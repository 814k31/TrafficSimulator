// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "CarCameraWidget.h"


void UCarCameraWidget::closeCamera()
{
	instigator->OnClickFunctionality();

	//Fill with functions to close camera and back to pawn

//	instigator->setHasBeenClicked(false);

//	ATrafficSimGameMode* currentGameMode = (ATrafficSimGameMode*)GetWorld()->GetAuthGameMode();
//	GetWorld()->GetFirstPlayerController()->Possess(currentGameMode->getPlayer());
//	RemoveFromViewport();
}

void UCarCameraWidget::setInstigator(AMyCar* newCar)
{
	instigator = newCar;
}

AMyCar* UCarCameraWidget::getInstigator()
{
	return instigator;
}