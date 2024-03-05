// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Struct/EQStructEnumBase.h"
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
};
