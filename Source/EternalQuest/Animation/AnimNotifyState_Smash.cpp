// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_Smash.h"

#include "AI/EQMonsterAbility.h"
#include "Character/EQBerserkerOrc.h"

void UAnimNotifyState_Smash::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float FrameDeltaTime)
{
	if(AEQBerserkerOrc* Temp = Cast<AEQBerserkerOrc>(MeshComp->GetOwner()))
	{
		Temp->CheckAttack_R(Temp->Ability->BerserkerSmashDamage);
	}
}
