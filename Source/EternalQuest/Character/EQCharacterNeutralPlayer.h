// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "Containers/Deque.h"
#include "Interface/EQInterfaceNPCPrompt.h"
#include "EQCharacterNeutralPlayer.generated.h"

class AEQItemBase;
class UNiagaraComponent;
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
	virtual void QuestAccepted() override;
	virtual void QuestDenied() override;
	virtual void QuestSuccess() override;
	// ----- 오버라이드 함수 -----

	// ----- 변수 -----
	FString NPCName;
	TDeque<FString> NPCPrompt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> ClothComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> QuestIcon;

	UPROPERTY()
	TSubclassOf<AActor> SpawnItemFactory;

	UPROPERTY()
	TObjectPtr<UDataTable> ItemDataTable;
	// ----- 변수 -----
};
