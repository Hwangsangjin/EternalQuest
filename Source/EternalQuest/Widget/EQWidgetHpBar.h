// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EQWidgetBase.h"
#include "EQWidgetHpBar.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class ETERNALQUEST_API UEQWidgetHpBar : public UEQWidgetBase
{
	GENERATED_BODY()
	
public:
	UEQWidgetHpBar(const FObjectInitializer& ObjectInitialzer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp, float NewMaxHp);

	FString GetHpText();

protected:
	UPROPERTY()
	TObjectPtr<UProgressBar> ProgressBar_Hp;

	UPROPERTY()
	TObjectPtr<UTextBlock> TextBlock_Hp;

	UPROPERTY()
	float CurrentHp;

	UPROPERTY()
	float MaxHp;
};
