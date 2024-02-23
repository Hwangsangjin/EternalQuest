// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQBTTask_MeleeAttack.h"

#include "AIController.h"
#include "EQMonsterAbility.h"
#include "Character/EQBerserkerOrc.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

UEQBTTask_MeleeAttack::UEQBTTask_MeleeAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("MeleeAttack");
}

EBTNodeResult::Type UEQBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp,Warning,TEXT("BerserkerAttack"));
	auto const * const Controller = OwnerComp.GetAIOwner();
	auto Monster = Controller->GetPawn();
	auto Orc = Cast<AEQBerserkerOrc>(Monster);
	if(Orc)
	{
		MonsterCheckHit(OwnerComp);
		Orc->PlayAnimMontage(Montage,1.f,FName("Attack1"));
		//Orc->PlayAnimMontage(Montage,1.f,FName("Attack2"));
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		Orc->Ability->bIsHit = false;
		return EBTNodeResult::Succeeded;	
	}
	return EBTNodeResult::Failed;
}

void UEQBTTask_MeleeAttack::MonsterCheckHit(UBehaviorTreeComponent& OwnerComp)
{
	auto const * const Controller = OwnerComp.GetAIOwner();
	auto Monster = Controller->GetPawn();
	auto Self = Cast<AEQBerserkerOrc>(Monster);
	FHitResult HitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack),false,Self);
	float MeleeRange = 100.f;
	float MeleeAttackRad = 50.f;
	float Damage = 5;
	FVector StartLoc = Self->GetActorLocation() + Self->GetActorForwardVector() * Self->GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + Self->GetActorForwardVector() * MeleeRange;
	DrawDebugSphere(GetWorld(),StartLoc,MeleeAttackRad,100,FColor::Red,false,2,0);

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult,StartLoc,EndLoc,FQuat::Identity,ECC_GameTraceChannel1,FCollisionShape::MakeSphere(MeleeAttackRad),Params);
	if(bHit)
	{
		FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(Damage,DamageEvent,nullptr,Self);
	}
}


