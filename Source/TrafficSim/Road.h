// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <map>

#include "MyCar.h"
#include "Road.generated.h"

UCLASS()
class ARoad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoad();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Declare box overlap event function
	UFUNCTION()
		void enteredBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		//void enteredBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Declare box leave event function
	UFUNCTION()
		virtual void leftBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		//void leftBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnClick(class UPrimitiveComponent* OtherComp, FKey inKey);
		//void OnClick(class UPrimitiveComponent* OtherComp);

	//method to calculate all the average speed from all the cars and the ratio of drivers on the road
	void calcAvgSpeedAndRatio();

	//Returns average speed on the road
	float getAvgSpeed();

	int32 getSafeTally();
	int32 getNormalTally();
	int32 getAggressiveTally();

	//method to get the number of vehicles on the road
	int32 getVehicleCount();

	//Function to initialise the direction vector.
	//This was used initially to give the roads a direction which
	//we planned to use to direct the vehicles.
	//May be redundant now.
	void InitDirectionVector();

	//Used for statistics
	void tallyCarTypes(int32 inType, int32* inRatioSafe, int32* inRatioNorm, int32* inRatioAggressive);

protected:
	//Collision box
	UPROPERTY(BluePrintReadOnly)
		UBoxComponent* box;

	//Direction box (only created to give a visual representation of which direction the road is for a developer)
	UPROPERTY(BlueprintReadOnly)
		UBoxComponent* directionBox;

	//Road static mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* myMesh;

	//Road Speed limit
	UPROPERTY(BlueprintReadWrite)
		int32 maxDrivingSpeed;

	//Each vehicle on the road is added to the map
	std::map<uint32, AMyCar*> vehicleMap;
	int32 mapSize;

	//Different materials set if a road is selected or not
	UMaterial* matGlow;
	UMaterial* mat;

	//Direction of the road - may be redundant
	FVector directionVector;

	//True if the user has clicked the roads static mesh
	bool hasBeenClicked;

	//Used to get statistics on the road.
	int32 ratioSafe, ratioNorm, ratioAggressive;
	float avgSpeed;
};
