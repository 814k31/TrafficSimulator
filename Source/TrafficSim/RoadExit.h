// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Road.h"
#include "RoadExit.generated.h"

UCLASS()
class ARoadExit : public ARoad
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoadExit();

	UPROPERTY(BlueprintReadOnly)
		UBoxComponent* exitBox;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Override onclick function so that the road exit doesnt have any click functionality
	UFUNCTION()
		virtual void OnClick(class UPrimitiveComponent* OtherComp);

	UFUNCTION()
		//void killCar(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		void killCar(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
