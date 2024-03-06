// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EQPlayerController.h"
#include "EternalQuest.h"
#include "Blueprint/UserWidget.h"
#include "Component/EQComponentInventory.h"
#include "GameFramework/Character.h"
#include "Widget/EQWidgetMainUI.h"

AEQPlayerController::AEQPlayerController()
{
	
	static ConstructorHelpers::FClassFinder<UEQWidgetMainUI> MainUIRef(TEXT("/Game/Blueprints/UI/WBP_WidgetMain.WBP_WidgetMain_C"));
	if (MainUIRef.Succeeded())
	{
		MainUIFactory = MainUIRef.Class;
	}
}

void AEQPlayerController::PostInitializeComponents()
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostInitializeComponents();

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
	
}

void AEQPlayerController::PostNetInit()
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ServerConnection)
		{
			EQ_LOG(LogEternalQuest, Log, TEXT("Server Connection: %s"), *NetDriver->ServerConnection->GetName());
		}
	}
	else
	{
		EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("No NetDriver"));
	}

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
}

void AEQPlayerController::OnPossess(APawn* InPawn)
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::OnPossess(InPawn);

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
	
}

void AEQPlayerController::BeginPlay()
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::BeginPlay();

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	
	EQWidgetMainUI = Cast<UEQWidgetMainUI>(CreateWidget(GetWorld(), MainUIFactory));
	if (EQWidgetMainUI && IsLocalController())
	{
		EQWidgetMainUI->AddToViewport();
		auto Inventory = GetCharacter()->FindComponentByClass<UEQComponentInventory>();
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,TEXT("123"));
		Inventory->LoadInventory();
	}

	EQWidgetMainUI->SetVisibility(ESlateVisibility::Visible);
}

void AEQPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEQPlayerController::CreateMainWidget()
{
	if (!EQWidgetMainUI)
	{
		FInputModeGameOnly InputModeGameOnly;
		SetInputMode(InputModeGameOnly);

		EQWidgetMainUI = Cast<UEQWidgetMainUI>(CreateWidget(GetWorld(), MainUIFactory));
		if (EQWidgetMainUI && IsLocalController())
		{
			EQWidgetMainUI->AddToViewport();
		}
	}
}
