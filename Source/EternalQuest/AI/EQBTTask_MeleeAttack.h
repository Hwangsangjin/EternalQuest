// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EQBTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UEQBTTask_MeleeAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animaiton")
	UAnimMontage* Montage;

private:
	void MonsterCheckHit(UBehaviorTreeComponent& OwnerComp);
};
