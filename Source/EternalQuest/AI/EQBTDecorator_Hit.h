// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "EQBTDecorator_Hit.generated.h"

class UEQMonsterAbility;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTDecorator_Hit : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UEQBTDecorator_Hit();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere)
	UEQMonsterAbility* MonsterAbility;
	
};
