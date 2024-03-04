// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNeutralPlayer.h"
#include "EQCharacterNeutralPlayerSeungTae.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQCharacterNeutralPlayerSeungTae : public AEQCharacterNeutralPlayer
{
	GENERATED_BODY()
public:
	AEQCharacterNeutralPlayerSeungTae();
	
	// ----- 오버라이드 함수 -----
	virtual void BeginPlay() override;
	virtual void QuestAccepted() override;
	virtual void QuestDenied() override;
	virtual void QuestSuccess() override;
	// ----- 오버라이드 함수 -----

	
};
