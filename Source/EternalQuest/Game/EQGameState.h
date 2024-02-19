// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "EQGameState.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void HandleBeginPlay() override;
	virtual void OnRep_ReplicatedHasBegunPlay();
};
