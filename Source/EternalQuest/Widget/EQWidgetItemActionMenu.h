// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetItemActionMenu.generated.h"

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
	UFUNCTION()
	void OnHoverBtnUse();
	UFUNCTION()
	void OnUnhoverBtnUse();
	UFUNCTION()
	void OnHoverBtnDrop();
	UFUNCTION()
	void OnUnhoverBtnDrop();
	UFUNCTION()
	void OnHoverBtnCancel();
	UFUNCTION()
	void OnUnhoverBtnCancel();

	
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
};
