// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTService_ChangeSpeed.h"

#include "EQAIController.h"
#include "Character/EQBerserkerOrc.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

UEQBTService_ChangeSpeed::UEQBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
}

void UEQBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if(auto const Controller = OwnerComp.GetAIOwner())
	{
		if(auto* const Orc = Cast<AEQBerserkerOrc>(Controller->GetPawn()))
		{
			Orc->GetCharacterMovement()->MaxWalkSpeed = Speed;
		}
	}
}
