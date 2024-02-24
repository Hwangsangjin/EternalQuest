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

	static ConstructorHelpers::FObjectFinder<UInputAction> CallStatusRef(TEXT("/Game/Blueprints/Input/Actions/IA_CallStatus.IA_CallStatus"));
	if (CallStatusRef.Object)
	{
		CallStatusAction = CallStatusRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CallSkillRef(TEXT("/Game/Blueprints/Input/Actions/IA_CallSkill.IA_CallSkill"));
	if (CallSkillRef.Object)
	{
		CallSkillAction = CallSkillRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> CallQuestRef(TEXT("/Game/Blueprints/Input/Actions/IA_CallQuest.IA_CallQuest"));
	if (CallQuestRef.Object)
	{
		CallQuestAction = CallQuestRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CallSettingsRef(TEXT("/Game/Blueprints/Input/Actions/IA_CallSettings.IA_CallSettings"));
	if (CallSettingsRef.Object)
	{
		CallSettingsAction = CallSettingsRef.Object;
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
		EnhancedInputComponent->BindAction(CallStatusAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::CallStatus);
		EnhancedInputComponent->BindAction(CallSkillAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::CallSkill);
		EnhancedInputComponent->BindAction(CallQuestAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::CallQuest);
		EnhancedInputComponent->BindAction(CallSettingsAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::CallSettings);
		EnhancedInputComponent->BindAction(MouseModeAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::FlipFlopMouseMode);
	}
}

void UEQComponentMenuManager::CallInventory(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickInventory();
}

void UEQComponentMenuManager::CallStatus(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickStatus();
}

void UEQComponentMenuManager::CallSkill(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickSkill();
}

void UEQComponentMenuManager::CallQuest(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickQuest();
}

void UEQComponentMenuManager::CallSettings(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickSettings();
}

void UEQComponentMenuManager::FlipFlopMouseMode(const FInputActionValue& Value)
{
	if (bMouseModeFlag)
	{
		bMouseModeFlag = false;
		EQPlayerController->SetShowMouseCursor(false);
		const FInputModeGameOnly GameOnly;
		EQPlayerController->SetInputMode(GameOnly);
	}
	else
	{
		bMouseModeFlag = true;
		EQPlayerController->SetShowMouseCursor(true);
		const FInputModeGameAndUI GameAndUI;
		EQPlayerController->SetInputMode(GameAndUI);
	}
}
