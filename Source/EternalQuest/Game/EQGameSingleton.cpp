// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EQGameSingleton.h"

DEFINE_LOG_CATEGORY(LogEQGameSingleton);

UEQGameSingleton::UEQGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/Blueprints/Data/DT_CharacterStat.DT_CharacterStat'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FEQCharacterStat*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0);
}

UEQGameSingleton& UEQGameSingleton::Get()
{
	UEQGameSingleton* Singleton = CastChecked<UEQGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogEQGameSingleton, Error, TEXT("Invalid Game Singleton"));
	return *NewObject<UEQGameSingleton>();
}
