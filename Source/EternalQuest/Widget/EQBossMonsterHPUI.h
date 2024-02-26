// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQBossMonsterHPUI.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQBossMonsterHPUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,meta=(BindWidget))
	UProgressBar* BossHPBar;
	UPROPERTY(EditDefaultsOnly,meta=(BindWidget))
	UProgressBar* BossHPBar_1;
	UPROPERTY(EditDefaultsOnly,meta=(BindWidget))
	UTextBlock* Txt_BarCount;

public:
	float SavePercent = 1;

	int32 Baridx = 0;
	int32 DevideValue = 1500;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UProgressBar>> HPBarArray;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void UpdateHP(float CurrentHealth, float MaxHealth);
};
