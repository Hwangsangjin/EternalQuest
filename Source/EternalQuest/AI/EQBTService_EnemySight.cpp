// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTService_EnemySight.h"

#include "AIController.h"
#include "EQMonsterAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/EQBerserkerOrc.h"
#include "Character/EQCharacterPlayer.h"

UEQBTService_EnemySight::UEQBTService_EnemySight()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Enemy Sight");
}

void UEQBTService_EnemySight::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	auto const Controller = OwnerComp.GetAIOwner();
	auto Monster = Controller->GetPawn();
	auto Berserker = Cast<AEQBerserkerOrc>(Monster);
	auto Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
	auto Player = Cast<AEQCharacterPlayer>(Target);

	FVector PlayerPos = Player->GetActorLocation();
	FVector SelfPos = Berserker->GetActorLocation();
	FVector DirectionToPlayer = PlayerPos - SelfPos;
	DirectionToPlayer.Normalize();

	FVector SelfForwardVector = Berserker->GetActorForwardVector();
	float DotProduct = FVector::DotProduct(SelfForwardVector,DirectionToPlayer);
	float ConeHalfAngle = FMath::DegreesToRadians(45.0f);
	float ConeLength = 500.0f;
	DrawDebugCone(GetWorld(), SelfPos, DirectionToPlayer, ConeLength, ConeHalfAngle, ConeHalfAngle, 12, FColor::Green, false, 2.f, 0, 10.f);
	if (DotProduct > 0)
	{
		if (DotProduct > 0.6)
		{
			Berserker->Ability->bIsHit = false;
			Berserker->MultiRPC_Dodge();
		}
	}
	
}
