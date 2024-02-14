// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetInventory.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetInventory : public UUserWidget
{
	GENERATED_BODY()

public:

	// ----- 함수 -----
	void OpenCloseInventoryWidget();
	// ----- 함수 -----
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	USizeBox* SizeBox_Base;

	bool bVisibilityFlag = false;
	
};
