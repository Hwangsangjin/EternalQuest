// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentBase.h"
#include "EQComponentQuest.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALQUEST_API UEQComponentQuest : public UEQComponentBase
{
	GENERATED_BODY()

	UEQComponentQuest();
public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InspectingItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<uint8> QuestStateArray;

	bool bQuestCond1 = false;
	bool bQuestCond2 = false;
	bool bQuestCond3 = false;
	int32 bQuestCond3Quantity = 0;
	bool bQuestCond4 = false;
};
