// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTDecorator_MeleeAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQCharacterPlayer.h"

UEQBTDecorator_MeleeAttackRange::UEQBTDecorator_MeleeAttackRange()
{
	NodeName = "Is MeleeAttack Range";
}

bool UEQBTDecorator_MeleeAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	auto const Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	auto const*const Controller = OwnerComp.GetAIOwner();
	auto const*const Orc = Controller->GetPawn();
	auto Player = Cast<AEQCharacterPlayer>(Target);
	if(Player)
	{
		float Dist = FVector::Dist(Player->GetActorLocation(),Orc->GetActorLocation());
		if(BerserkerAttackRange >= Dist)
		{
			return true;
		}
	}
	return false;
}
