// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterEnemy.h"

#include "AI/EQMonsterAbility.h"

AEQCharacterEnemy::AEQCharacterEnemy()
{
	Ability = CreateDefaultSubobject<UEQMonsterAbility>(TEXT("Ability"));
}

float AEQCharacterEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Ability->TakeDamage(this,DamageAmount,Type,EventInstigator,DamageCauser);

	return DamageAmount;
}
