// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EQBTTask_Die.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTTask_Die : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UEQBTTask_Die();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	float DieTime = 5.0f;
};
