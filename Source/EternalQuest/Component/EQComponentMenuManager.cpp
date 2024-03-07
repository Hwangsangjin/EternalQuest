// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentMenuManager.h"

#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Player/EQPlayerController.h"
#include "Widget/EQWidgetIconBar.h"
#include "Widget/EQWidgetInventory.h"
#include "Widget/EQWidgetMainUI.h"
#include "Widget/EQWidgetPostBox.h"
#include "Widget/EQWidgetQuestList.h"
#include "Widget/EQWidgetSkill.h"
#include "Widget/EQWidgetStateUI.h"
#include "Widget/EQWidgetStatus.h"

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
	
	static ConstructorHelpers::FObjectFinder<UInputAction> CallPostBoxRef(TEXT("/Game/Blueprints/Input/Actions/IA_CallPostBox.IA_CallPostBox"));
	if (CallPostBoxRef.Object)
	{
		CallPostBoxAction = CallPostBoxRef.Object;
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

	PrimaryComponentTick.bCanEverTick = true;
}

void UEQComponentMenuManager::BeginPlay()
{
	Super::BeginPlay();
	// EQComponentInventory = Player->FindComponentByClass<UEQComponentInventory>();
	
}

void UEQComponentMenuManager::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bStateFlag)
	{
		if (StatePos.X < 550)
		{
			StatePos = FMath::Vector2DInterpTo(StatePos, FVector2D(560,0), DeltaTime, 8);
		}
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStatus->SetRenderTransform(FWidgetTransform(StatePos, FVector2D(1), FVector2D(0), 0));
	}
	
	if (bInventoryFlag)
	{
		if (InventoryPos.X > -550)
		{
			InventoryPos = FMath::Vector2DInterpTo(InventoryPos, FVector2D(-560,0), DeltaTime, 8);
		}
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInventory->SetRenderTransform(FWidgetTransform(InventoryPos, FVector2D(1), FVector2D(0), 0));
	}

	if (bSkillFlag)
	{
		if (SkillPos.X > -550)
		{
			SkillPos = FMath::Vector2DInterpTo(SkillPos, FVector2D(-560,0), DeltaTime, 8);
		}
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetSkill->SetRenderTransform(FWidgetTransform(SkillPos, FVector2D(1), FVector2D(0), 0));
	}

	if (bQuestFlag)
	{
		if (QuestPos.X < 550)
		{
			QuestPos = FMath::Vector2DInterpTo(QuestPos, FVector2D(560,0), DeltaTime, 8);
		}
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetQuestList->SetRenderTransform(FWidgetTransform(QuestPos, FVector2D(1), FVector2D(0), 0));
	}

	if (bPostBoxFlag)
	{
		if (PostBoxPos.X < 550)
		{
			PostBoxPos = FMath::Vector2DInterpTo(PostBoxPos, FVector2D(560,0), DeltaTime, 8);
		}
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetPostBox->SetRenderTransform(FWidgetTransform(PostBoxPos, FVector2D(1), FVector2D(0), 0));
	}

	if (bUIRefresh == false)
	{
		CurrTimeUIRefresh+=DeltaTime;
	}
	
	if (CurrTimeUIRefresh > 10.f)
	{
		bUIRefresh = true;
		CurrTimeUIRefresh = 0;
		SeamlessTravelUIRefresh();
	}
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
		EnhancedInputComponent->BindAction(CallPostBoxAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::CallPostBox);
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
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStatus->InitUpdateStat();
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->AddCallBackFunc();
}

void UEQComponentMenuManager::CallSkill(const FInputActionValue& Value)
{
	auto SkillWidget = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSkill;

	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickSkill();
	SkillWidget->UpdateSkillPnt();
}

void UEQComponentMenuManager::CallQuest(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickQuest();
}

void UEQComponentMenuManager::CallPostBox(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickPostBox();
}

void UEQComponentMenuManager::CallSettings(const FInputActionValue& Value)
{
	EQPlayerController->EQWidgetMainUI->WBP_EQWidgetIconBar->OnClickSettings();
}

void UEQComponentMenuManager::FlipFlopMouseMode(const FInputActionValue& Value)
{
	if (bMouseModeFlag)
	{
		SeamlessTravelUIRefresh();
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

void UEQComponentMenuManager::SeamlessTravelUIRefresh()
{
	// Cast<AEQCharacterPlayer>(GetOwner())->CreateMinimap();

	EQPlayerController->UIRefresh();
	
	Cast<AEQCharacterPlayer>(GetOwner())->CreateMinimap();
}

void UEQComponentMenuManager::ClearPos()
{
	bInventoryFlag = false;
	bStateFlag = false;
	bSkillFlag = false;
	bQuestFlag = false;
	bPostBoxFlag = false;

	InventoryPos = FVector2D(0);
	StatePos = FVector2D(0);
	SkillPos = FVector2D(0);
	QuestPos = FVector2D(0);
	PostBoxPos = FVector2D(0);
}
