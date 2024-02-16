// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/EQStructEnumBase.h"
#include "EQWidgetItemInfo.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetItemInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void UpdateItemInfo(const FEQSlot& InItem);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Description;
};
