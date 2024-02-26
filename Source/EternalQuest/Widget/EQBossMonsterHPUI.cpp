// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQBossMonsterHPUI.h"

#include "Components/ProgressBar.h"

void UEQBossMonsterHPUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// float NewPercent = FMath::Lerp(BossHPBar->GetPercent(),TargetPercent,InDeltaTime * 5);
	// BossHPBar->SetPercent(NewPercent);
}

void UEQBossMonsterHPUI::UpdateHP(float CurrentHealth, float MaxHealth)
{
	// maxHP = 1000
	// MaxHP = 3000
	// 2분할 = 1500
	// 2분할 500
	// int32 현재체력바 idx = 0;

	//BossHPBar  = CurrentHealth/MaxHealth;
	// currHp 체력 줄인다
	// 0 보다 작거나 같아졌다면
	// 현재체력바 idx++
	// if(idx >= 2) 죽음
	// else currHP = 500 + currHP
	
	// currHp / 500 ---> 
	
	
	
	
	// 임계값을 설정해서 그 값이 넘으면 몬스터의 체력창을 증가시킨다.
	// 지금 보스의 체력은 3000
	// float FirstHealthBarPercent = CurrentHealth / MaxHealth;
	// BossHPBar_1 -> SetPercent(FirstHealthBarPercent);
	// float SecondHPBarPercent = 0;
	// BossHPBar ->SetPercent(SecondHPBarPercent);
	// SavePercent = (CurrentHealth - 0.5 * MaxHealth) / (0.5 * MaxHealth);
	// if (BossHPBar_1->GetPercent() < 0.5)
	// {
	// 	SecondHPBarPercent = (CurrentHealth - 0.5 * MaxHealth) / (0.5 * MaxHealth);
	// 	FirstHealthBarPercent = 0.5;
	// }
	// BossHPBar_1->SetPercent(FirstHealthBarPercent);
	// BossHPBar->SetPercent(SecondHPBarPercent);


	// int HpBar = MaxHealth / HPBarArray.Num();
	// for(int32 i = HPBarArray.Num(); i>=0; i--)
	// {
	// 	
	// }
}
