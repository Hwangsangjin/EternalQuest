// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/EQStructEnumBase.h"
#include "EQWidgetItemSlot.generated.h"

class UTextBlock;
class USizeBox;
class UImage;
class UBorder;
class UEQWidgetInventory;
class UButton;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Slot;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBorder> Border_Item;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Img_HoverTriangle;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Img_Item;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Quantity;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Quantity;

	UPROPERTY()
	TObjectPtr<UEQWidgetInventory> EQWidgetInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEQSlot EQSlot;

	UFUNCTION()
	void OnHoverBtnSlot();
	UFUNCTION()
	void OnUnhoverBtnSlot();
};
