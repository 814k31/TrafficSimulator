// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "RoadEntry.h"
#include "RoadEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRAFFICSIM_API URoadEntryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//When a road entry is clicked it is set as the instigator for the widget
	//This means that the widget can only edit one road entry at a time
	void setInstigator(ARoadEntry* inRoadEntry);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Widget Setup")
		void loadValues();

	UFUNCTION(BlueprintCallable, Category = "Widget Setup")
		ARoadEntry* getInstigator();

	//The instigator is the ARoadEntry object that is clicked
	UPROPERTY(BlueprintReadOnly, Category = "Widget Setup")
		ARoadEntry* Instigator;

	UPROPERTY(BlueprintReadWrite, Category = "Widget Setup")
		bool hasBeenSet;
};
