// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQDamageAmoutUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQDamageAmoutUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI",meta=(BindWidget))
	UTextBlock* Txt_Damage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI",meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* Fade;
	void ShowDamageAmount(float Damage);
};
