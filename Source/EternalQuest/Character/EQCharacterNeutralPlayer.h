// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "Containers/Deque.h"
#include "Interface/EQInterfaceNPCPrompt.h"
#include "EQCharacterNeutralPlayer.generated.h"

class UEQWidgetNpcPrompt;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQCharacterNeutralPlayer : public AEQCharacterNonPlayer, public IEQInterfaceNPCPrompt
{
	GENERATED_BODY()
public:
	AEQCharacterNeutralPlayer();
	// ----- 오버라이드 함수 -----
	virtual void BeginPlay() override;
	// ----- 오버라이드 함수 -----

	// ----- 변수 -----
	FString NPCName;
	TDeque<FString> NPCPrompt;

	virtual void QuestAccepted() override;
	virtual void QuestDenied() override;
	// ----- 변수 -----
};
