// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CustomCamera.h"
#include "GameFramework/GameMode.h"
#include "TrafficSimGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ATrafficSimGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATrafficSimGameMode(const FObjectInitializer& ObjectInitializer);

	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void InitializeWidget(TSubclassOf<UUserWidget> NewWidgetClass);
		//void InitializeMenuWidget(UUserWidget* NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void StartButtonFunc();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void PauseButtonFunc();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ResetButtonFunc();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void RemoveWidget();

	ACustomCamera* getPlayer();

protected:
	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
		UUserWidget* CurrentWidget;

	ACustomCamera* defaultPawnInstance;
};
