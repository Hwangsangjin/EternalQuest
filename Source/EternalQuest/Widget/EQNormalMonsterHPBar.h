// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQNormalMonsterHPBar.generated.h"

class AEQNormalEnemy;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQNormalMonsterHPBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI",meta=(BindWidget))
	UProgressBar* HPBar;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI",meta=(BindWidget))
	UTextBlock* Txt_MonsterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEQNormalEnemy* NormalEnemy;
	UFUNCTION(BlueprintCallable)
	void GetMonsterName();
	UFUNCTION(BlueprintCallable)
	void UpdateHP(float CurrentHealth,float MaxHealth);
};
