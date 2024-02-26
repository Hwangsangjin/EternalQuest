// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetStateUI.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetStateUI : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void UpdateStateUI(float InCurrentHP);
	void SetMaxHP();

	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UProgressBar> Prog_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UProgressBar> Prog_MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UProgressBar> Prog_EXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_UserName;
};
