// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetStateUI.generated.h"

class UImage;
class UEQComponentStat;
class UTextBlock;
class UProgressBar;
/**
 * 		StatComp->SetHp(StatComp->GetCurrentHp() + UseItem->Healing);

 */
UCLASS()
class ETERNALQUEST_API UEQWidgetStateUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetStateUI(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

	void UpdateStateUI(float InCurrentHP, float InMaxHP);
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> Img_JobClass;

	UPROPERTY()
	TObjectPtr<UEQComponentStat> StatComp;

	UPROPERTY()
	TObjectPtr<UTexture2D> T_WarriorIcon;

	UPROPERTY()
	TObjectPtr<UTexture2D> T_MageIcon;
};
