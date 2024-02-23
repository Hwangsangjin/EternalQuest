// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTTask_ChaseTarget.h"

#include "EQAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/EQCharacterPlayer.h"

UEQBTTask_ChaseTarget::UEQBTTask_ChaseTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Target");
}

EBTNodeResult::Type UEQBTTask_ChaseTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto* const Controller = Cast<AEQAIController>(OwnerComp.GetAIOwner()))
	{
		//선택된 키값의 위치를 가져와서
		auto const Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
		auto Player = Cast<AEQCharacterPlayer>(Target);
		if(Player)
		{
			FVector TargetLoc = Player->GetActorLocation() - 100.f;
			// 그위치로 이동시킨다.
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller,TargetLoc);
			FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
