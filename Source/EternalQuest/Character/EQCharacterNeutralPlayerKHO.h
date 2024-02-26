// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNeutralPlayer.h"
#include "EQCharacterNeutralPlayerKHO.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQCharacterNeutralPlayerKHO : public AEQCharacterNeutralPlayer
{
	GENERATED_BODY()
public:
	AEQCharacterNeutralPlayerKHO();
	
	// ----- 오버라이드 함수 -----
	virtual void BeginPlay() override;
	virtual void QuestAccepted() override;
	virtual void QuestDenied() override;
	// ----- 오버라이드 함수 -----
};
