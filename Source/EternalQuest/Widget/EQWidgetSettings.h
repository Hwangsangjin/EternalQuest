// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetSettings.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetSettings : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnClickedSetting();
	UFUNCTION()
	void OnClickedExit();
	UFUNCTION()
	void OnClickedCancel();
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_Settings;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_Exit;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_Cancel;
};
