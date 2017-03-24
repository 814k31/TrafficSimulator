// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TrafficSim.h"
#include "TrafficSimGameMode.h"
#include "CustomCamera.h"
#include "StatisticsHUD.h"
#include "CustomCameraController.h"

//Parent Class of Blueprint game mode set in editor (MenuGameMode)

ATrafficSimGameMode::ATrafficSimGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Set up default classes - these can be edited within the unreal editor
	DefaultPawnClass = ACustomCamera::StaticClass();
	HUDClass = AStatisticsHUD::StaticClass();
}

void ATrafficSimGameMode::BeginPlay()
{
    Super::BeginPlay();
	//Call function to display the play, pause and reset button
	InitializeWidget(StartingWidgetClass);
	defaultPawnInstance = (ACustomCamera*) GetWorld()->GetFirstPlayerController()->GetPawn();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

//Create a menu widget when the simulation is started
void ATrafficSimGameMode::InitializeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (NewWidgetClass != nullptr)
    {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

//Triggered when start button is clicked
void ATrafficSimGameMode::StartButtonFunc()
{
	//Fill with function to start simulation
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

//Triggered when pause button is clicked
void ATrafficSimGameMode::PauseButtonFunc()
{
	//Fill with function to pause simulation
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

//Triggered when reset button is clicked
void ATrafficSimGameMode::ResetButtonFunc()
{
	//Fill with function to reset simulation
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

//Removes the widget from the users viewpoint
void ATrafficSimGameMode::RemoveWidget()
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
}

ACustomCamera* ATrafficSimGameMode::getPlayer()
{
	return defaultPawnInstance;
}
