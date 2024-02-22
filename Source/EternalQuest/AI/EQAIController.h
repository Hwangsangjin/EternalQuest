// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EQAIController.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQAIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit AEQAIController(FObjectInitializer const& ObjectInitializer);


protected:
	virtual void OnPossess(APawn* InPawn) override;
};
