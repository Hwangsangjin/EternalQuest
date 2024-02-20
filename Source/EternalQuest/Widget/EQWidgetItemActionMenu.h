// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EQWidgetItemSlot.h"
#include "Blueprint/UserWidget.h"
#include "Struct/EQStructEnumBase.h"
#include "EQWidgetItemActionMenu.generated.h"

class UEQWidgetItemSlot;
struct FEQSlot;
class UTextBlock;
class USizeBox;
class UButton;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetItemActionMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void BringItemSlotRef(UEQWidgetItemSlot*& InItemSlot);
	
	UFUNCTION()
	void OnHoverBtnUse();
	UFUNCTION()
	void OnUnhoverBtnUse();
	UFUNCTION()
	void OnClickBtnUse();
	UFUNCTION()
	void OnHoverBtnDrop();
	UFUNCTION()
	void OnUnhoverBtnDrop();
	UFUNCTION()
	void OnClickBtnDrop();
	UFUNCTION()
	void OnHoverBtnCancel();
	UFUNCTION()
	void OnUnhoverBtnCancel();
	UFUNCTION()
	void OnClickBtnCancel();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Base;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Use;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Drop;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Cancel;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Use;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Drop;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Cancel;

	UPROPERTY()
	TObjectPtr<UEQWidgetInventory> EQWidgetInventory;
	
	FEQSlot* EQSlot;

	UPROPERTY()
	TObjectPtr<UEQWidgetItemSlot> EQWidgetItemSlot;
};
