// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTDecorator_Hit.h"

#include "AIController.h"
#include "EQMonsterAbility.h"
#include "Character/EQBossEnemy.h"

UEQBTDecorator_Hit::UEQBTDecorator_Hit()
{
	NodeName = "Is Monster Hit";
}

bool UEQBTDecorator_Hit::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto const * const Controller = OwnerComp.GetAIOwner();
	auto Monster = Controller->GetPawn();
	auto Orc = Cast<AEQBossEnemy>(Monster);
	return Orc->GetIsMonsterHit();
	//return Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
}
