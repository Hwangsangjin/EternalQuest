// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AvoidableCheck.h"
#include "Interface/EQInterfaceAnimationAvoid.h"

void UAnimNotify_AvoidableCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IEQInterfaceAnimationAvoid* AvoidPawn = Cast<IEQInterfaceAnimationAvoid>(MeshComp->GetOwner());
		if (AvoidPawn)
		{
			AvoidPawn->AvoidableCheck();
		}
	}
}
