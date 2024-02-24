// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTTask_Smash.h"

#include "EQAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQBerserkerOrc.h"
#include "Character/EQCharacterPlayer.h"

UEQBTTask_Smash::UEQBTTask_Smash(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Smash");
}

EBTNodeResult::Type UEQBTTask_Smash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp,Warning,TEXT("BerserkerAttack"));
	auto const Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	auto Player = Cast<AEQCharacterPlayer>(Target);
	auto const Controller = Cast<AEQAIController>(OwnerComp.GetAIOwner());
	auto Monster = Controller->GetPawn();
	auto Orc = Cast<AEQBerserkerOrc>(Monster);
	if(Orc)
	{
		Controller->SetFocus(Player,EAIFocusPriority::Gameplay);
		Orc->PlayAnimMontage(Montage,1.f,FName("Smash"));
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		//Orc->Ability->bIsHit = false;
		return EBTNodeResult::Succeeded;	
	}
	return EBTNodeResult::Failed;
}
