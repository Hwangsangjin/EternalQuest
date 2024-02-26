// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/EQCharacterStat.h"
#include "EQGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogEQGameSingleton, Error, All);

UCLASS()
class ETERNALQUEST_API UEQGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UEQGameSingleton();
	static UEQGameSingleton& Get();

// Character Stat
public:
	FORCEINLINE FEQCharacterStat GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel) ? CharacterStatTable[InLevel] : FEQCharacterStat(); }

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FEQCharacterStat> CharacterStatTable;
};
