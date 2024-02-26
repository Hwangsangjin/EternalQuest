// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EQBTService_EnemySight.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTService_EnemySight : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UEQBTService_EnemySight();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage;
};
