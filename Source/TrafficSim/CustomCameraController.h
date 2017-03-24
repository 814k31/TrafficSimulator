// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h" 
#include "Road.h"
#include "RoadEntry.h"
#include "RoadEntryWidget.h"
#include "MyCar.h"
#include "CarCameraWidget.h"
#include <set>
#include "CustomCameraController.generated.h"

/**
 * 
 */
UCLASS()
class TRAFFICSIM_API ACustomCameraController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/*//Called at the start of the game
	virtual void BeginPlay() override;
	//Called with every frame
	virtual void Tick(float DeltaSeconds) override;
	*/
	//Triggered when a road is clicked - called by ARoad class
	void addClickedRoad(ARoad* clickedRoad, bool hasBeenClicked);
	//Triggered when a road entry is clicked - called by ARoadEntry class
	void addClickedRoadEntry(ARoadEntry* inClickedEntry);
	void removeClickedRoadEntry(ARoadEntry* inClickedEntry);

	//Triggered when a cars static mesh is clicked
	void carClick(AMyCar* clickedCar);
	void carUnClick(AMyCar* clickedCar);

	//Calculates speed and ratio such that methods only need to have one loop in a tick function
	void calcAvgSpeedAndRatio();
	//Loops through clickedRoads set and returns the total number of vehicles on all the selecte roads
	int32 getAllClickedCarCount();
	//Loops through clickedRoads set and returns the average speed of the vehicles on all the selecte roads
	float getAllClickedSpeed();

	//This variable has to be set in the Controller's blueprint before running the game otherwise it will cause a NULL pointer exception
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class URoadEntryWidget> entryWidgetReference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UCarCameraWidget> carWidgetReference;

	//Have to do it this way to parse in the selected road entry into the widget
	UFUNCTION(BlueprintCallable, Category = RoadEntry)
	ARoadEntry* getClickedRoadEntry();

	//Used for statistics
	int32 getSafeRatio();
	int32 getNormalRatio();
	int32 getAggressiveRatio();

protected:
	//More than one road can be clicked at one time
	std::set<ARoad*> clickedRoads;
	//Only one entry can be clicked at one time
	URoadEntryWidget* clickedEntryWidget;

	UCarCameraWidget* clickedCarWidget;

	//Clicked road entry
	ARoadEntry* clickedRoadEntry;
	AMyCar* clickedCar;

	//This method of calculating statistics is used to increase a small overhead instead of
	//having multiple loops in a tick function.
	float avgSpeed;
	int32 ratioSafeDriver;
	int32 ratioNormalDriver;
	int32 ratioAggressiveDriver;

	bool bCarBeenClicked;
	bool roadEntryWidgetVisible;
};