// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EQCharacterComboAttackData.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQCharacterComboAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UEQCharacterComboAttackData() = default;

// Combo Attack Data
public:
	FORCEINLINE FString GetMontageSectionNamePrefix() const { return MontageSectionNamePrefix; }
	FORCEINLINE uint8 GetMaxComboCount() const { return MaxComboCount; }
	FORCEINLINE float GetFrameRate() const { return FrameRate; }
	FORCEINLINE TArray<float> GetEffectiveFrameCount() const { return EffectiveFrameCount; }

private:
	UPROPERTY(EditAnywhere, Category = Name, Meta = (AllowPrivateAccess = true))
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnywhere, Category = Name, Meta = (AllowPrivateAccess = true))
	uint8 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = Name, Meta = (AllowPrivateAccess = true))
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = ComboData, Meta = (AllowPrivateAccess = true))
	TArray<float> EffectiveFrameCount;
};
