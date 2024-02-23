// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EQBTTask_MeleeComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTTask_MeleeComboAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	explicit UEQBTTask_MeleeComboAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	UAnimMontage* Montage;
};
