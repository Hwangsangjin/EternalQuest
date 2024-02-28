// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTService_HealthRecovery.h"

#include "AIController.h"
#include "EQMonsterAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQBerserkerOrc.h"

UEQBTService_HealthRecovery::UEQBTService_HealthRecovery(FObjectInitializer const& ObjectInitializer)
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Health Recovery");
}

void UEQBTService_HealthRecovery::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if(auto const * const Controller = OwnerComp.GetAIOwner())
	{
		auto Self = Controller->GetPawn();
		auto Orc = Cast<AEQBerserkerOrc>(Self);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("RecoveryHPRate"),0.003);
		float RecoveryRate = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
		if (Orc->Ability->CurrentHealth < Orc->Ability-> MaxHealth)
		{
			float RecoveryAmount = Orc->Ability-> MaxHealth * RecoveryRate;
			Orc->Ability->CurrentHealth += RecoveryAmount;
			Orc->Ability->CurrentHealth = FMath::Min(Orc->Ability->CurrentHealth, Orc->Ability-> MaxHealth);
		}
	}
}
