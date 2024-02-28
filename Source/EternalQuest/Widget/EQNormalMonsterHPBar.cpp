// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQNormalMonsterHPBar.h"

#include "Character/EQNormalEnemy.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UEQNormalMonsterHPBar::GetMonsterName()
{
	FString NormalEnemyName = NormalEnemy->SetName();
	Txt_MonsterName->SetText(FText::FromString(NormalEnemyName));
}

void UEQNormalMonsterHPBar::UpdateHP(float CurrentHealth, float MaxHealth)
{
	HPBar->SetPercent(CurrentHealth/MaxHealth);
}
