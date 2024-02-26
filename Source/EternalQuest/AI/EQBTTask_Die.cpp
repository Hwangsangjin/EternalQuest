// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTTask_Die.h"

#include "EQAIController.h"
#include "EQMonsterAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQBerserkerOrc.h"
#include "Character/EQBossEnemy.h"

UEQBTTask_Die::UEQBTTask_Die()
{
	NodeName = TEXT("Die");
}

EBTNodeResult::Type UEQBTTask_Die::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Controller = Cast<AEQAIController>(OwnerComp.GetAIOwner());
	auto Self = Controller->GetPawn();
	auto Orc = Cast<AEQBerserkerOrc>(Self);
	float CurrentTime = 0;
	CurrentTime += GetWorld()->GetDeltaSeconds();
	bool Check = Orc->GetIsMonsterDie();
	UE_LOG(LogTemp,Warning,TEXT("Check : %d"),Check);
	Orc->MultiRPC_Die();
	if(CurrentTime > DieTime)
	{
		Orc->Destroy();
		
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
