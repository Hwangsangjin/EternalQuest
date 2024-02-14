// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetInteract.generated.h"

class USizeBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetInteract : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void InteractShowItem();
	void InteractShowNPC();
	void InteractDisable();
	// ----- 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	USizeBox* SizeBox_Switch;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Txt_InputKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* Txt_Detail;
	// ----- 변수 -----
};
