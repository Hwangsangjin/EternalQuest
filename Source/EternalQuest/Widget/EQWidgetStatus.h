// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetStatus.generated.h"

class UImage;
class UEQComponentStat;
class UButton;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetStatus : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetStatus(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void InitUpdateStat();
	void UpdateStatUp();
	UFUNCTION()
	void UpdateState(float InCurrentHP, float InMaxHP);
	void UpdateAdditionalStat();

	UFUNCTION()
	void OnClickedIncreaseHP();

	UFUNCTION()
	void OnClickedIncreaseMP();

	UFUNCTION()
	void OnClickedIncreaseSTR();

	UFUNCTION()
	void OnClickedIncreaseINT();

	UFUNCTION()
	void OnClickedIncreaseDEF();

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_StatPoint;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_StateHP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_StateMP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_StateXP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_OriginHP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_OriginMP;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_OriginSTR;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_OriginINT;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_OriginDEF;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_AdditionalHP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_AdditionalMP;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_AdditionalSTR;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_AdditionalINT;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_AdditionalDEF;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> Prog_HP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> Prog_MP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> Prog_STR;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> Prog_INT;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> Prog_DEF;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_IncreaseHP;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_IncreaseMP;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_IncreaseSTR;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_IncreaseINT;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_IncreaseDEF;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Img_ThumbnailCharacter;

	UPROPERTY()
	TObjectPtr<UTexture2D> T_Warrior;
	
	UPROPERTY()
	TObjectPtr<UTexture2D> T_Mage;

	UPROPERTY()
	TObjectPtr<UEQComponentStat> StatComp;

	// 임시 변수 //
	// float CurrentPointHP;
	// float CurrentPointMP;
	// float CurrentPointSTR;
	// float CurrentPointINT;
	// float CurrentPointDEF;

	float SumMaxHP;
	float SumMaxMP;
	float SumSTR;
	float SumINT;
	float SumDEF;

	float MaxPoint = 10;
	int32 StatPoint = 50; // 레벨을 올릴 수 있는 포인트

	UPROPERTY()
	TObjectPtr<USoundWave> StatPointClickSound;
};
