// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EQCharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FEQCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FEQCharacterStat() : MaxHp(0.0f), MaxExp(0.0f), AttackDamage(0.0f), AttackRange(0.0f), AttackRadius(0.0f), AttackSpeed(100.0f), MovementSpeed(450.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	FEQCharacterStat operator+(const FEQCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FEQCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FEQCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		uint32 uMaxHp = (uint32)MaxHp;
		Ar.SerializeIntPacked(uMaxHp);
		MaxHp = (float)uMaxHp;

		uint32 uMaxExp = (uint32)MaxExp;
		Ar.SerializeIntPacked(uMaxExp);
		MaxExp = (float)uMaxExp;

		uint32 uAttackDamage = (uint32)AttackDamage;
		Ar.SerializeIntPacked(uAttackDamage);
		AttackDamage = (float)uAttackDamage;

		uint32 uAttackRange = (uint32)AttackRange;
		Ar.SerializeIntPacked(uAttackRange);
		AttackRange = (float)uAttackRange;

		uint32 uAttackRadius = (uint32)AttackRadius;
		Ar.SerializeIntPacked(uAttackRadius);
		AttackRadius = (float)uAttackRadius;

		uint32 uAttackSpeed = (uint32)AttackSpeed;
		Ar.SerializeIntPacked(uAttackSpeed);
		AttackSpeed = (float)uAttackSpeed;

		uint32 uMovementSpeed = (uint32)MovementSpeed;
		Ar.SerializeIntPacked(uMovementSpeed);
		MovementSpeed = (float)uMovementSpeed;

		return true;
	}
	
};

template<>
struct TStructOpsTypeTraits<FEQCharacterStat> : public TStructOpsTypeTraitsBase2<FEQCharacterStat>
{
	enum
	{
		WithNetSerializer = true
	};
};
