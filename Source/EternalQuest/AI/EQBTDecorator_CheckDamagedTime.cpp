// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTDecorator_CheckDamagedTime.h"

#include "AIController.h"
#include "EQMonsterAbility.h"
#include "Character/EQBerserkerOrc.h"

UEQBTDecorator_CheckDamagedTime::UEQBTDecorator_CheckDamagedTime()
{
	NodeName = TEXT("Check DamagedTime");
}

bool UEQBTDecorator_CheckDamagedTime::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	auto const * const Controller = OwnerComp.GetAIOwner();
	auto Self = Controller->GetPawn();
	auto Boss = Cast<AEQBossEnemy>(Self);
	if(Boss)
	{
		if(Boss->Ability->bIsDamageOver == true)
		{
			Boss->Ability->DamageReceiver = 0.f;
			Boss->Ability->bIsDamageOver = false;
			return true;
		}
		return false;
	}
	return false;
}
