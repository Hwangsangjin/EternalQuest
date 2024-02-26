// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTDecorator_IsDead.h"

#include "AIController.h"
#include "EQMonsterAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQBerserkerOrc.h"
#include "Character/EQBossEnemy.h"

UEQBTDecorator_IsDead::UEQBTDecorator_IsDead()
{
	NodeName = TEXT("Check Die");
}

bool UEQBTDecorator_IsDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto const * const Controller = OwnerComp.GetAIOwner();
	auto Self = Controller->GetPawn();
	auto Boss = Cast<AEQBossEnemy>(Self);
	if(Boss)
	{
		if(Boss->GetIsMonsterDie() == true)
		{
			return false;
		}
		return true;
	}
	return false;
}
