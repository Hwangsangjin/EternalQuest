// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetStateUI.h"

#include "Component/EQComponentStat.h"
#include "Components/ProgressBar.h"
#include "GameFramework/Character.h"
#include "Player/EQPlayerController.h"

void UEQWidgetStateUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetMaxHP();
}

void UEQWidgetStateUI::UpdateStateUI(float InCurrentHP)
{
	if (Prog_HP)
	{
		Prog_HP->SetPercent(InCurrentHP/MaxHP);
	}
}

void UEQWidgetStateUI::SetMaxHP()
{
	auto StatComp = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->GetCharacter()->FindComponentByClass<UEQComponentStat>();
	MaxHP = StatComp->GetMaxHp();
}
