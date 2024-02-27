// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQBossMonsterHPUI.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"

void UEQBossMonsterHPUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	
}

void UEQBossMonsterHPUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// float NewPercent = FMath::Lerp(BossHPBar->GetPercent(),TargetPercent,InDeltaTime * 5);
	// BossHPBar->SetPercent(NewPercent);
}

void UEQBossMonsterHPUI::UpdateHP(float CurrentHealth, float MaxHealth)
{
	
	const int32 LineCount = MaxHealth / BarLimit;
	Txt_BarCount->SetText(FText::FromString(FString::Printf(TEXT("X%d"),LineCount)));
	if(!(MaxHealth/BarLimit) == 0)
	{
		//반올림한 값이 줄의 개수
	}
	const float LimitHealth = MaxHealth/LineCount;
	if(CurrentHealth > LimitHealth)
	{
		BossHPBar_1->SetPercent((CurrentHealth-LimitHealth)/LimitHealth);
		BossHPBar->SetPercent(1.f);
	}
	else
	{
		BossHPBar_1->SetPercent(0.f);
		BossHPBar->SetPercent(CurrentHealth/LimitHealth);
	}
}


