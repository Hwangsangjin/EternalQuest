// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetDragItem.generated.h"

class UEQWidgetInventory;
struct FEQSlot;
class UImage;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetDragItem : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> Img_Thumbnail;

	FEQSlot* EQSlot;

	UPROPERTY()
	TObjectPtr<UEQWidgetInventory> EQWidgetInventory;
};
