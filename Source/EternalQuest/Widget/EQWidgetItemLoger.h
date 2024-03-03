// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetItemLoger.generated.h"

class UEQWidgetItemLogMessage;
struct FEQSlot;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetItemLoger : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetItemLoger(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void SetItemLogMessage(const FEQSlot& InSlot);

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox_Base;

	UPROPERTY()
	TSubclassOf<UUserWidget> LogMessageFactory;
};
