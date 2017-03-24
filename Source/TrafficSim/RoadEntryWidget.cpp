// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficSim.h"
#include "RoadEntryWidget.h"



//The instigator is the road which the widget will edit.
void URoadEntryWidget::setInstigator(ARoadEntry* inRoadEntry)
{
	Instigator = inRoadEntry;
	hasBeenSet = true;
UE_LOG(LogTemp, Warning, TEXT("Road Entry has been set!"));
}

//Function to allow child classes in blueprint to access variable without making it public
ARoadEntry* URoadEntryWidget::getInstigator()
{
	return Instigator;
}

//Expecting this function to be overriden by blueprint child class
void URoadEntryWidget::loadValues_Implementation()
{}