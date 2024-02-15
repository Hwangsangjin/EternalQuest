// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetMainUI.generated.h"

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
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEQWidgetInteract> WBP_EQWidgetInteract;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEQWidgetIconBar> WBP_EQWidgetIconBar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEQWidgetInventory> WBP_EQWidgetInventory;
};
