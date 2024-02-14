// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EQPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Widget/EQWidgetMainUI.h"

AEQPlayerController::AEQPlayerController()
{
	static ConstructorHelpers::FClassFinder<UEQWidgetMainUI> MainUIRef(TEXT("/Game/LDJ/UI/WBP_WidgetMain.WBP_WidgetMain_C"));
	if (MainUIRef.Succeeded())
	{
		MainUIFactory = MainUIRef.Class;
	}
}

void AEQPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}

void AEQPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	EQWidgetMainUI = Cast<UEQWidgetMainUI>(CreateWidget(GetWorld(), MainUIFactory));
	if (EQWidgetMainUI && IsLocalController())
	{
		EQWidgetMainUI->AddToViewport();
	}
}
