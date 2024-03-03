// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetItemLogMessage.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetItemLogMessage : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Img_ItemThumbnail;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ItemName;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ItemQuantity;

	float CurrTime;
	float CurrentOpacity;
	float CurrentTranslationX;
	float CurrentTranslationY = -50;
};
