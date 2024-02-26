// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTTask_MeleeComboAttack.h"

#include "EQAIController.h"
#include "EQMonsterAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQBerserkerOrc.h"
#include "Character/EQCharacterPlayer.h"

UEQBTTask_MeleeComboAttack::UEQBTTask_MeleeComboAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "MeleeComboAttack";
}

EBTNodeResult::Type UEQBTTask_MeleeComboAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp,Warning,TEXT("Combo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"));
	auto const Controller = Cast<AEQAIController>(OwnerComp.GetAIOwner());
	auto Monster = Controller->GetPawn();
	auto Orc = Cast<AEQBerserkerOrc>(Monster);
	auto Target = Controller->GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	auto Player = Cast<AEQCharacterPlayer>(Target);
	if(Orc)
	{
		Controller->StopMovement();
		Controller->SetFocus(Player,EAIFocusPriority::Gameplay);
		Orc->MultiRPC_Combo();
		Controller->GetBlackboardComponent()->SetValueAsFloat(FName(TEXT("CurrentTime")), 0);
		Orc->Ability->bIsHit = false;
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
