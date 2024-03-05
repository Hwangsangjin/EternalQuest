// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentQuest.h"
#include "Component/EQComponentStat.h"
#include "GameFramework/SaveGame.h"
#include "Struct/EQStructEnumBase.h"
#include "Widget/EQWidgetSkill.h"
#include "EQSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FEQAllItem EQAllItem;

	UPROPERTY()
	FEQStatusStat StatusStat;

	UPROPERTY()
	FEQQuestProgress QuestCondition;

	UPROPERTY()
	FEQSkill EQSkill;
};
