// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQBossMonsterHPUI.h"

#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UEQBossMonsterHPUI::NativeConstruct()
{
	Super::NativeConstruct();

	BarIdx = 2;
	ChangePhase = 1000;
	
}

void UEQBossMonsterHPUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// float NewPercent = FMath::Lerp(BossHPBar->GetPercent(),TargetPercent,InDeltaTime * 5);
	// BossHPBar->SetPercent(NewPercent);
}

void UEQBossMonsterHPUI::UpdateHP(float Health)
{
	
	auto FirstBar = UKismetMathLibrary::MapRangeClamped(Health,0.5,1,0,1);
	
	BossHPBar_1->SetPercent(FirstBar);
	auto SecondBar = UKismetMathLibrary::MapRangeClamped(Health,0,0.5,0,1);
	
	BossHPBar->SetPercent(SecondBar);
	
}
