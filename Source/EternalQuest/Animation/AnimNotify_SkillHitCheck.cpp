// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SkillHitCheck.h"
#include "Interface/EQInterfaceAnimationSkill.h"

void UAnimNotify_SkillHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IEQInterfaceAnimationSkill* SkillPawn = Cast<IEQInterfaceAnimationSkill>(MeshComp->GetOwner());
		if (SkillPawn)
		{
			SkillPawn->SkillHitCheck();
		}
	}
}
