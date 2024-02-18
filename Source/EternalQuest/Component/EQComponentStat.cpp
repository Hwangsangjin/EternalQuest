// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentStat.h"

UEQComponentStat::UEQComponentStat()
	: MaxHp(200.0f)
	, CurrentHp(MaxHp)
{
}

void UEQComponentStat::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);
}

float UEQComponentStat::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}

void UEQComponentStat::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}
