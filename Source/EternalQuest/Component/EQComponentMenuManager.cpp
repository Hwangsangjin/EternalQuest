// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentMenuManager.h"

#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Player/EQPlayerController.h"
#include "Widget/EQWidgetIconBar.h"
#include "Widget/EQWidgetInventory.h"
#include "Widget/EQWidgetMainUI.h"

UEQComponentMenuManager::UEQComponentMenuManager()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> CallInventoryRef(TEXT("/Game/Blueprints/Input/Actions/IA_CallInventory.IA_CallInventory"));
	if (CallInventoryRef.Object)
	{
		CallInventoryAction = CallInventoryRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseModeRef(TEXT("/Game/Blueprints/Input/Actions/IA_MouseMode.Ia_MouseMode"));
	if (MouseModeRef.Object)
	{
		MouseModeAction = MouseModeRef.Object;
	}
}

void UEQComponentMenuManager::BeginPlay()
{
	Super::BeginPlay();
	EQComponentInventory = Player->FindComponentByClass<UEQComponentInventory>();
}

void UEQComponentMenuManager::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQComponentMenuManager::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(CallInventoryAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::CallInventory);
		EnhancedInputComponent->BindAction(MouseModeAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::FlipFlopMouseMode);
	}
}

void UEQComponentMenuManager::CallInventory(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickInventory();
}

void UEQComponentMenuManager::FlipFlopMouseMode(const FInputActionValue& Value)
{
	if (bMouseModeFlag)
	{
		bMouseModeFlag = false;
		EQPlayerController->SetShowMouseCursor(false);
		const FInputModeGameOnly GameOnly;
		EQPlayerController->SetInputMode(GameOnly);
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, TEXT("Closed"));
	}
	else
	{
		bMouseModeFlag = true;
		EQPlayerController->SetShowMouseCursor(true);
		const FInputModeGameAndUI GameAndUI;
		EQPlayerController->SetInputMode(GameAndUI);
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, TEXT("Open"));
	}
}
