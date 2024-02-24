// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetChatMessage.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetChatMessage : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ChatDetail;

	UPROPERTY()
	FText PlayerName;

	UPROPERTY()
	FText ChatDetail;
};
