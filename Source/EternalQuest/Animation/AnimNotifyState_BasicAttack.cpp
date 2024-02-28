// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_BasicAttack.h"

#include "InputBehavior.h"
#include "ToolContextInterfaces.h"
#include "AI/EQMonsterAbility.h"
#include "Character/EQBerserkerOrc.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"


void UAnimNotifyState_BasicAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                              float FrameDeltaTime)
{
	if(AEQBerserkerOrc* Temp = Cast<AEQBerserkerOrc>(MeshComp->GetOwner()))
	{
		
		Temp->CheckAttack_L(Temp->Ability->BerserkerBasicAttackDamage);
		Temp->CheckAttack_R(Temp->Ability->BerserkerBasicAttackDamage);
	}
}
