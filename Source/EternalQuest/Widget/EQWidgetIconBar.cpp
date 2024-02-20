// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetIconBar.h"

#include "EQWidgetInventory.h"
#include "EQWidgetMainUI.h"
#include "Components/Button.h"
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

	Btn_Settings->OnHovered.AddDynamic(this, &UEQWidgetIconBar::OnHoverSettings);
	Btn_Settings->OnUnhovered.AddDynamic(this, &UEQWidgetIconBar::OnUnhoverSettings);
	Btn_Settings->OnClicked.AddDynamic(this, &UEQWidgetIconBar::OnClickSettings);

	EQPlayerController = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController());
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
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, TEXT("CloseStatus"));
	}
	else
	{
		ClearIconFlag();
		OnHoverStatus();
		bOpenStatus = true;
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, TEXT("OpenStatus"));
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
	}
	else
	{
		ClearIconFlag();
		OnHoverInventory();
		bOpenInventory = true;
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInventory->OpenCloseInventoryWidget();
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
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, TEXT("CloseSkill"));
	}
	else
	{
		ClearIconFlag();
		OnHoverSkill();
		bOpenSkill = true;
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, TEXT("OpenSkill"));
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
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, TEXT("CloseQuest"));
	}
	else
	{
		ClearIconFlag();
		OnHoverQuest();
		bOpenQuest = true;
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, TEXT("OpenQuest"));
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
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, TEXT("CloseSettings"));
	}
	else
	{
		ClearIconFlag();
		OnHoverSettings();
		bOpenSettings = true;
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Green, TEXT("OpenSettings"));
	}
}

void UEQWidgetIconBar::ClearIconFlag()
{
	bOpenStatus = false;
	if (bOpenInventory)
	{
		bOpenInventory = false;
		OnUnhoverInventory();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInventory->OpenCloseInventoryWidget();
	}
	bOpenSkill = false;
	bOpenQuest = false;
	bOpenSettings = false;
	OnUnhoverStatus();
	OnUnhoverInventory();
	OnUnhoverSkill();
	OnUnhoverQuest();
	OnUnhoverSettings();
}

