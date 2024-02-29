// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetStateUI.h"

#include "Component/EQComponentStat.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Game/EQGameInstance.h"
#include "GameFramework/Character.h"

UEQWidgetStateUI::UEQWidgetStateUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> T_WarriorIconRef(TEXT("/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_game/icon_game_163.icon_game_163"));
	if (T_WarriorIconRef.Succeeded()) T_WarriorIcon = T_WarriorIconRef.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T_MageIconRef(TEXT("/Game/Assets/CleanFlatIcons/Textures/png_128/icon/icon_game/icon_game_180.icon_game_180"));
	if (T_MageIconRef.Succeeded()) T_MageIcon = T_MageIconRef.Object;
}

void UEQWidgetStateUI::NativeConstruct()
{
	Super::NativeConstruct();
	auto ClassType = Cast<UEQGameInstance>(GetWorld()->GetGameInstance())->GetClassType();
	if (ClassType == EClassType::ECT_Mage)
	{
		Img_JobClass->SetBrushFromTexture(T_MageIcon);
	}
	else if (ClassType == EClassType::ECT_Warrior)
	{
		Img_JobClass->SetBrushFromTexture(T_WarriorIcon);
	}
	StatComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentStat>();
	StatComp->OnHpChanged.AddUObject(this, &ThisClass::UpdateStateUI);
	SetMaxHP();
}

void UEQWidgetStateUI::UpdateStateUI(float InCurrentHP, float InMaxHP)
{
	if (Prog_HP)
	{
		Prog_HP->SetPercent(InCurrentHP/InMaxHP);
	}
}

void UEQWidgetStateUI::SetMaxHP()
{
	MaxHP = StatComp->GetMaxHp();
}
