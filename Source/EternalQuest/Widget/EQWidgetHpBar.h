// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EQWidgetBase.h"
#include "EQWidgetHpBar.generated.h"

class UProgressBar;

UCLASS()
class ETERNALQUEST_API UEQWidgetHpBar : public UEQWidgetBase
{
	GENERATED_BODY()
	
public:
	UEQWidgetHpBar(const FObjectInitializer& ObjectInitialzer);

protected:
	virtual void NativeConstruct() override;

// Hp
public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);

protected:
	UPROPERTY()
	TObjectPtr<UProgressBar> ProgressBar_Hp;

	UPROPERTY()
	float MaxHp;
};
