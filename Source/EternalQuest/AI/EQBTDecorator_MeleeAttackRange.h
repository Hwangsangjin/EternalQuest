// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "EQBTDecorator_MeleeAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTDecorator_MeleeAttackRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UEQBTDecorator_MeleeAttackRange();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess = "true"))
	float BerserkerAttackRange = 400.f;
	
};
