// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EQBTService_HealthRecovery.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBTService_HealthRecovery : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UEQBTService_HealthRecovery(FObjectInitializer const& ObjectInitializer);
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
