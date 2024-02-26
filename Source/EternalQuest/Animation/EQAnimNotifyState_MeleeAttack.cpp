// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EQAnimNotifyState_MeleeAttack.h"

#include "Character/EQBerserkerOrc.h"
#include "Engine/DamageEvents.h"

void UEQAnimNotifyState_MeleeAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                float FrameDeltaTime)
{
	auto Orc = Cast<AEQBerserkerOrc>(MeshComp->GetOwner());
	FVector StartLoc = Orc->WeaponComp_L->GetSocketLocation("Axe_StartPos");
	FVector EndLoc = Orc->WeaponComp_L->GetSocketLocation("Axe_EndPos");
	float MeleeAttackRad = 40.f; 
	float Damage = 10.f;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack),false,Orc);
	FHitResult HitResult;
	DrawDebugSphere(GetWorld(),StartLoc,MeleeAttackRad,100,FColor::Red,false,2.0f,0,5);
	bool bHit = GetWorld()->SweepSingleByChannel(HitResult,StartLoc,EndLoc,FQuat::Identity,ECC_GameTraceChannel1,FCollisionShape::MakeSphere(MeleeAttackRad),Params);
	{
		if(bHit)
		{
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(Damage,DamageEvent,nullptr,Orc);
		}
	}
}


