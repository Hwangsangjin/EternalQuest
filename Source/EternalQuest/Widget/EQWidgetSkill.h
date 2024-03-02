// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetSkill.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetSkill : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetSkill(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<USoundWave> SkillPointClickSound;
};
