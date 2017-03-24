// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Road.h"
#include "Blueprint/UserWidget.h"
#include "RoadEntry.generated.h"

/**
 *
 */
UCLASS()
class ARoadEntry : public ARoad
{
	GENERATED_BODY()

	public:
	// Sets default values for this actor's properties
		ARoadEntry();

		UPROPERTY(BlueprintReadOnly)
		UBoxComponent* spawnBox;

		// Called every frame
		virtual void Tick(float DeltaSeconds) override;

		UFUNCTION()
		//virtual void leftBox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		virtual void leftBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

		//Override onclick function so that the road entry can be customised to call a parameter widget
		UFUNCTION()
			virtual void OnClick(class UPrimitiveComponent* OtherComp);

		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			void OnClickFunctionality();

		//functions to allow for editing parameters
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			int32 getSpawnRate();
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			int32 getRatioSafe();
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			int32 getRatioNormal();
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			int32 getRatioAggressive();

		//Defaults for default button
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			int32 getDefaultRatioSafe();
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			int32 getDefaultRatioNormal();
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			int32 getDefaultRatioAggressive();
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			int32 getDefaultSpawnRate();

		

		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			void setSpawnRate(int32 inSpawnRate);
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			void setRatioSafe(int32 inRatioSafe);
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			void setRatioNormal(int32 inRatioNormal);
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			void setRatioAggressive(int32 inRatioAggressive);

		//These functions are called by roadentrywidget.cpp for error checking
		bool getIsClicked();
		UFUNCTION(BlueprintCallable, Category = RoadEntry)
			void setIsClicked(bool newBeenClicked);

private:
		//spawnRate increments with each tick
		int32 spawnRate;
		//spawnTime is the time between spawns
		int32 spawnTime;

		//Ratio variables to control spawning
		int32 ratioSafe;
		int32 ratioNormal;
		int32 ratioAggressive;

		//Defaults for default button
		int32 defaultRatioSafe;
		int32 defaultRatioNormal;
		int32 defaultRatioAggressive;
		int32 defaultSpawnRate;
		bool canSpawn;
};