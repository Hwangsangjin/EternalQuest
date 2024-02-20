// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetMainUI.generated.h"

class UEQWidgetItemDropArea;
class UEQWidgetItemActionMenu;
class UEQWidgetInventory;
class UEQWidgetIconBar;
class UEQWidgetInteract;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetMainUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEQWidgetInteract> WBP_EQWidgetInteract;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEQWidgetIconBar> WBP_EQWidgetIconBar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEQWidgetInventory> WBP_EQWidgetInventory;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEQWidgetItemActionMenu> WBP_EQWidgetItemActionMenu;
};
