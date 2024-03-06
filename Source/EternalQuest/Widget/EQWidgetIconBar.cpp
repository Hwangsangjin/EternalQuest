// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetIconBar.h"

#include "EQWidgetBindKeySkillBar.h"
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

UEQWidgetIconBar::UEQWidgetIconBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> UIOpenSoundRef(TEXT("/Script/Engine.SoundWave'/Game/Assets/RPG_Interface_SFX/WAV/UI_Menu_01.UI_Menu_01'"));
	if (UIOpenSoundRef.Succeeded())
	{
		UIOpenSound = UIOpenSoundRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundWave> UICloseSoundRef(TEXT("/Script/Engine.SoundWave'/Game/Assets/RPG_Interface_SFX/WAV/UI_Menu_02.UI_Menu_02'"));
	if (UICloseSoundRef.Succeeded())
	{
		UICloseSound = UICloseSoundRef.Object;
	}
}

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

	// EQPlayerController = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController());
	// MenuManager = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>();
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
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStatus->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UICloseSound);
	}
	else
	{
		ClearIconFlag();
		OnHoverStatus();
		bOpenStatus = true;
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStatus->SetVisibility(ESlateVisibility::Visible);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UIOpenSound);
	}

	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bStateFlag)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bStateFlag = false;
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->ClearPos();
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bStateFlag = true;
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
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory->OpenCloseInventoryWidget();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetBindKeySkillBar->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UICloseSound);
	}
	else
	{
		ClearIconFlag();
		OnHoverInventory();
		bOpenInventory = true;
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory->OpenCloseInventoryWidget();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetBindKeySkillBar->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UIOpenSound);
	}

	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bInventoryFlag)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bInventoryFlag = false;
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->ClearPos();
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bInventoryFlag = true;
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
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSkill->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetBindKeySkillBar->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UICloseSound);
	}
	else
	{
		ClearIconFlag();
		OnHoverSkill();
		bOpenSkill = true;
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSkill->SetVisibility(ESlateVisibility::Visible);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetBindKeySkillBar->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UIOpenSound);
	}
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bSkillFlag)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bSkillFlag = false;
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->ClearPos();
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bSkillFlag = true;
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
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetQuestList->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UICloseSound);
	}
	else
	{
		ClearIconFlag();
		OnHoverQuest();
		bOpenQuest = true;
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetQuestList->SetVisibility(ESlateVisibility::Visible);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetQuestList->UpdateQuestIcon();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UIOpenSound);
	}
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bQuestFlag)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bQuestFlag = false;
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->ClearPos();
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bQuestFlag = true;
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
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetPostBox->SetVisibility(ESlateVisibility::Hidden); // 변경
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UICloseSound);
	}
	else
	{
		ClearIconFlag();
		OnHoverPostBox();
		bOpenPostBox = true;
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetPostBox->SetVisibility(ESlateVisibility::Visible); // 변경
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStateUI->SetVisibility(ESlateVisibility::Hidden);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetMinimap->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UIOpenSound);
	}
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bPostBoxFlag)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bPostBoxFlag = false;
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->ClearPos();
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->bPostBoxFlag = true;
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
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSettings->SetVisibility(ESlateVisibility::Hidden);
		PlaySound(UICloseSound);
	}
	else
	{
		ClearIconFlag();
		OnHoverSettings();
		bOpenSettings = true;
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSettings->SetVisibility(ESlateVisibility::Visible);
		PlaySound(UIOpenSound);
	}
}

void UEQWidgetIconBar::ClearIconFlag()
{
	if (bOpenStatus)
	{
		bOpenStatus = false;
		OnUnhoverStatus();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStatus->SetVisibility(ESlateVisibility::Hidden);
	}
	if (bOpenInventory)
	{
		bOpenInventory = false;
		OnUnhoverInventory();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory->OpenCloseInventoryWidget();
	};
	if (bOpenSkill)
	{
		bOpenSkill = false;
		OnUnhoverSkill();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSkill->SetVisibility(ESlateVisibility::Hidden);
	}
	if (bOpenQuest)
	{
		bOpenQuest = false;
		OnUnhoverQuest();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetQuestList->SetVisibility(ESlateVisibility::Hidden);
	}
	if (bOpenPostBox)
	{
		bOpenPostBox = false;
		OnUnhoverPostBox();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetPostBox->SetVisibility(ESlateVisibility::Hidden);
	}
	if (bOpenSettings)
	{
		bOpenSettings = false;
		OnUnhoverSettings();
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSettings->SetVisibility(ESlateVisibility::Hidden);
	}
	OnUnhoverStatus();
	OnUnhoverInventory();
	OnUnhoverSkill();
	OnUnhoverQuest();
	OnUnhoverPostBox();
	OnUnhoverSettings();
	
	GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMenuManager>()->ClearPos();
}

