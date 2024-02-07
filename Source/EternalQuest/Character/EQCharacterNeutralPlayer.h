// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "EQCharacterNeutralPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQCharacterNeutralPlayer : public AEQCharacterNonPlayer
{
	GENERATED_BODY()
public:
	AEQCharacterNeutralPlayer();
	virtual void BeginPlay() override;
};
