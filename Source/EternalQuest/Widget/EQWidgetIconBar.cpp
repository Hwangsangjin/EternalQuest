// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetIconBar.h"

#include "EQWidgetInventory.h"
#include "EQWidgetMainUI.h"
#include "EQWidgetMinimap.h"
#include "EQWidgetPostBox.h"
#include "EQWidgetQuestList.h"
#include "EQWidgetSettings.h"
#include "EQWidgetSkill.h"
#include "EQWidgetStateUI.h"
#include "EQWidgetStatus.h"
#include "Component/EQComponentMenuManager.h"
#include "Components/Button.h"
#include "GameFramework/Character.h"
#include "Player/EQPlayerController.h"

void UEQWidgetIconBar::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Status->OnHovered.AddDynamic(this, &UEQWidgetIconBar::OnHoverStatus);
	Btn_Status->OnUnhovered.AddDynamic(this, &UEQWidgetIconBar::OnUnhoverStatus);
	Btn_Status->OnClicked.AddDynamic(this, &UEQWidgetIconBar::OnClickStatus);

	Btn_Inventory->OnHovered.AddDynamic(this, &UEQWidgetIconBar::OnHoverInventory);
	Btn_Inventory->OnUnhovered.AddDynamic(this, &UEQWidgetIconBar::OnUnhoverInventory);
	Btn_Inventory->OnClicked.AddDynamic(this, &UEQWidgetIconBar::OnClickInventory);

	Btn_Skill->OnHovered.AddDynamic(this, &UEQWidgetIconBar::OnHoverSkill);
	Btn_Skill->OnUnhovered.AddDynamic(this, &UEQWidgetIconBar::OnUnhoverSkill);
	Btn_Skill->OnClicked.AddDynamic(this, &UEQWidgetIconBar::OnClickSkill);

	Btn_Quest->OnHovered.AddDynamic(this, &UEQWidgetIconBar::OnHoverQuest);
	Btn_Quest->OnUnhovered.AddDynamic(this, &UEQWidgetIconBar::OnUnhoverQuest);
	Btn_Quest->OnClicked.AddDynamic(this, &UEQWidgetIconBar::OnClickQuest);

	Btn_PostBox->OnHovered.AddDynamic(this, &UEQWidgetIconBar::OnHoverPostBox);
	Btn_PostBox->OnUnhovered.AddDynamic(this, &UEQWidgetIconBar::OnUnhoverPostBox);
	Btn_PostBox->OnClicked.AddDynamic(this, &UEQWidgetIconBar::OnClickPostBox);

	Btn_Settings->OnHovered.AddDynamic(this, &UEQWidgetIconBar::OnHoverSettings);
	Btn_Settings->OnUnhovered.AddDynamic(this, &UEQWidgetIconBar::OnUnhoverSettings);
	Btn_Settings->OnClicked.AddDynamic(this, &UEQWidgetIconBar::OnClickSettings);

	EQPlayerController = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController());
	MenuManager = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>();
}

void UEQWidgetIconBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UEQWidgetIconBar::OnHoverStatus()
{
	Btn_Status->SetBackgroundColor(FLinearColor(1,1,1,1));
	Btn_Status->SetRenderScale(FVector2D(1.2));
}

void UEQWidgetIconBar::OnUnhoverStatus()
{
	if (bOpenStatus)
	{
		return;
	}
	Btn_Status->SetBackgroundColor(FLinearColor(1,1,1,0.5));
	Btn_Status->SetRenderScale(FVector2D(1));
}

void UEQWidgetIconBar::OnClickStatus()
{
	if (bOpenStatus)
	{
		bOpenStatus = false;
		ClearIconFlag();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStatus->SetVisibility(ESlateVisibility::Hidden);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ClearIconFlag();
		OnHoverStatus();
		bOpenStatus = true;
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStatus->SetVisibility(ESlateVisibility::Visible);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Hidden);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
	}

	
	if (MenuManager->bStateFlag)
	{
		MenuManager->bStateFlag = false;
	}
	else
	{
		MenuManager->ClearPos();
		MenuManager->bStateFlag = true;
	}
}

void UEQWidgetIconBar::OnHoverInventory()
{
	Btn_Inventory->SetBackgroundColor(FLinearColor(1,1,1,1));
	Btn_Inventory->SetRenderScale(FVector2D(1.2));
}

void UEQWidgetIconBar::OnUnhoverInventory()
{
	if (bOpenInventory)
	{
		return;
	}
	Btn_Inventory->SetBackgroundColor(FLinearColor(1,1,1,0.5));
	Btn_Inventory->SetRenderScale(FVector2D(1));
}

void UEQWidgetIconBar::OnClickInventory()
{
	if (bOpenInventory)
	{
		bOpenInventory = false;
		OnUnhoverInventory();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInventory->OpenCloseInventoryWidget();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ClearIconFlag();
		OnHoverInventory();
		bOpenInventory = true;
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInventory->OpenCloseInventoryWidget();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Hidden);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
	}

	if (MenuManager->bInventoryFlag)
	{
		MenuManager->bInventoryFlag = false;
	}
	else
	{
		MenuManager->ClearPos();
		MenuManager->bInventoryFlag = true;
	}
}

void UEQWidgetIconBar::OnHoverSkill()
{
	Btn_Skill->SetBackgroundColor(FLinearColor(1,1,1,1));
	Btn_Skill->SetRenderScale(FVector2D(1.2));
}

void UEQWidgetIconBar::OnUnhoverSkill()
{
	if (bOpenSkill)
	{
		return;
	}
	Btn_Skill->SetBackgroundColor(FLinearColor(1,1,1,0.5));
	Btn_Skill->SetRenderScale(FVector2D(1));
}

void UEQWidgetIconBar::OnClickSkill()
{
	if (bOpenSkill)
	{
		bOpenSkill = false;
		ClearIconFlag();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetSkill->SetVisibility(ESlateVisibility::Hidden);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ClearIconFlag();
		OnHoverSkill();
		bOpenSkill = true;
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetSkill->SetVisibility(ESlateVisibility::Visible);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Hidden);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
	}
	if (MenuManager->bSkillFlag)
	{
		MenuManager->bSkillFlag = false;
	}
	else
	{
		MenuManager->ClearPos();
		MenuManager->bSkillFlag = true;
	}
}

void UEQWidgetIconBar::OnHoverQuest()
{
	Btn_Quest->SetBackgroundColor(FLinearColor(1,1,1,1));
	Btn_Quest->SetRenderScale(FVector2D(1.2));
}

void UEQWidgetIconBar::OnUnhoverQuest()
{
	if (bOpenQuest)
	{
		return;
	}
	Btn_Quest->SetBackgroundColor(FLinearColor(1,1,1,0.5));
	Btn_Quest->SetRenderScale(FVector2D(1));
}

void UEQWidgetIconBar::OnClickQuest()
{
	if (bOpenQuest)
	{
		bOpenQuest = false;
		ClearIconFlag();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetQuestList->SetVisibility(ESlateVisibility::Hidden);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ClearIconFlag();
		OnHoverQuest();
		bOpenQuest = true;
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetQuestList->SetVisibility(ESlateVisibility::Visible);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Hidden);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
	}
	if (MenuManager->bQuestFlag)
	{
		MenuManager->bQuestFlag = false;
	}
	else
	{
		MenuManager->ClearPos();
		MenuManager->bQuestFlag = true;
	}
}

void UEQWidgetIconBar::OnHoverPostBox()
{
	Btn_PostBox->SetBackgroundColor(FLinearColor(1,1,1,1));
	Btn_PostBox->SetRenderScale(FVector2D(1.2));
}

void UEQWidgetIconBar::OnUnhoverPostBox()
{
	if (bOpenPostBox)
	{
		return;
	}
	Btn_PostBox->SetBackgroundColor(FLinearColor(1,1,1,0.5));
	Btn_PostBox->SetRenderScale(FVector2D(1));
}

void UEQWidgetIconBar::OnClickPostBox()
{
	if (bOpenPostBox)
	{
		bOpenPostBox = false;
		ClearIconFlag();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetPostBox->SetVisibility(ESlateVisibility::Hidden); // 변경
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ClearIconFlag();
		OnHoverPostBox();
		bOpenPostBox = true;
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetPostBox->SetVisibility(ESlateVisibility::Visible); // 변경
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Hidden);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
	}
	if (MenuManager->bPostBoxFlag)
	{
		MenuManager->bPostBoxFlag = false;
	}
	else
	{
		MenuManager->ClearPos();
		MenuManager->bPostBoxFlag = true;
	}
}

void UEQWidgetIconBar::OnHoverSettings()
{
	Btn_Settings->SetBackgroundColor(FLinearColor(1,1,1,1));
	Btn_Settings->SetRenderScale(FVector2D(1.2));
}

void UEQWidgetIconBar::OnUnhoverSettings()
{
	if (bOpenSettings)
	{
		return;
	}
	Btn_Settings->SetBackgroundColor(FLinearColor(1,1,1,0.5));
	Btn_Settings->SetRenderScale(FVector2D(1));
}

void UEQWidgetIconBar::OnClickSettings()
{
	if (bOpenSettings)
	{
		bOpenSettings = false;
		ClearIconFlag();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetSettings->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ClearIconFlag();
		OnHoverSettings();
		bOpenSettings = true;
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetSettings->SetVisibility(ESlateVisibility::Visible);
	}
}

void UEQWidgetIconBar::ClearIconFlag()
{
	if (bOpenStatus)
	{
		bOpenStatus = false;
		OnUnhoverStatus();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetStatus->SetVisibility(ESlateVisibility::Hidden);
	}
	if (bOpenInventory)
	{
		bOpenInventory = false;
		OnUnhoverInventory();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInventory->OpenCloseInventoryWidget();
	};
	if (bOpenSkill)
	{
		bOpenSkill = false;
		OnUnhoverSkill();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetSkill->SetVisibility(ESlateVisibility::Hidden);
	}
	if (bOpenQuest)
	{
		bOpenQuest = false;
		OnUnhoverQuest();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetQuestList->SetVisibility(ESlateVisibility::Hidden);
	}
	if (bOpenPostBox)
	{
		bOpenPostBox = false;
		OnUnhoverPostBox();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetPostBox->SetVisibility(ESlateVisibility::Hidden);
	}
	if (bOpenSettings)
	{
		bOpenSettings = false;
		OnUnhoverSettings();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetSettings->SetVisibility(ESlateVisibility::Hidden);
	}
	OnUnhoverStatus();
	OnUnhoverInventory();
	OnUnhoverSkill();
	OnUnhoverQuest();
	OnUnhoverPostBox();
	OnUnhoverSettings();
	
	MenuManager->ClearPos();
}

