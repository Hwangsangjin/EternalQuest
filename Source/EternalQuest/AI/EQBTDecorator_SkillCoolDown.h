// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "EQBTDecorator_SkillCoolDown.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTDecorator_SkillCoolDown : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	UEQBTDecorator_SkillCoolDown();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	bool bFlag = false;
};
