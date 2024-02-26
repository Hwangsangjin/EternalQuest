// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EQAnimNotifyState_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQAnimNotifyState_MeleeAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	
};
