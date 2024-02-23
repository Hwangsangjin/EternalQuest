// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EQBTTask_Smash.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTTask_Smash : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UEQBTTask_Smash(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	UAnimMontage* Montage;
};
