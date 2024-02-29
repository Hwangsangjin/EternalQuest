// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetStateUI.h"

#include "Component/EQComponentStat.h"
#include "Components/ProgressBar.h"
#include "GameFramework/Character.h"
#include "Player/EQPlayerController.h"

void UEQWidgetStateUI::NativeConstruct()
{
	Super::NativeConstruct();
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
