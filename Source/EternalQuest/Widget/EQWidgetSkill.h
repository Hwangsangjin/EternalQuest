// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetSkill.generated.h"

class UImage;
class UButton;
class UWidgetSwitcher;
class UTextBlock;

USTRUCT(BlueprintType, Atomic)
struct FEQSkill : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_WarriorSkill1 = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_WarriorSkill2 = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_WarriorSkill3 = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_WarriorSkill4 = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_WarriorSkill5 = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_MageSkill1 = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_MageSkill2 = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_MageSkill3 = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_MageSkill4 = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Pnt_MageSkill5 = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SkillPnt = 50;

};

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetSkill : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetSkill(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void UpdateSkillPnt();
	
	UFUNCTION()
	void ClearSkillText();

	UFUNCTION()
	void OnHoveredWarriorSkill1();
	UFUNCTION()
	void OnHoveredWarriorSkill2();
	UFUNCTION()
	void OnHoveredWarriorSkill3();
	UFUNCTION()
	void OnHoveredWarriorSkill4();
	UFUNCTION()
	void OnHoveredWarriorSkill5();

	UFUNCTION()
	void OnClickedWarriorSkill1();
	UFUNCTION()
	void OnClickedWarriorSkill2();
	UFUNCTION()
	void OnClickedWarriorSkill3();
	UFUNCTION()
	void OnClickedWarriorSkill4();
	UFUNCTION()
	void OnClickedWarriorSkill5();

	UFUNCTION()
	void OnHoveredMageSkill1();
	UFUNCTION()
	void OnHoveredMageSkill2();
	UFUNCTION()
	void OnHoveredMageSkill3();
	UFUNCTION()
	void OnHoveredMageSkill4();
	UFUNCTION()
	void OnHoveredMageSkill5();

	UFUNCTION()
	void OnClickedMageSkill1();
	UFUNCTION()
	void OnClickedMageSkill2();
	UFUNCTION()
	void OnClickedMageSkill3();
	UFUNCTION()
	void OnClickedMageSkill4();
	UFUNCTION()
	void OnClickedMageSkill5();

	UPROPERTY()
	TObjectPtr<USoundWave> SkillPointClickSound;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_JobName;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WS_SwitchSkillWindow;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_WarriorSkill1;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_WarriorSkill1Pnt;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_WarriorSkill2;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_WarriorSkill2Pnt;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_WarriorSkill3;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_WarriorSkill3Pnt;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_WarriorSkill4;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_WarriorSkill4Pnt;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_WarriorSkill5;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_WarriorSkill5Pnt;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_MageSkill1;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_MageSkill1Pnt;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_MageSkill2;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_MageSkill2Pnt;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_MageSkill3;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_MageSkill3Pnt;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_MageSkill4;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_MageSkill4Pnt;
    	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_MageSkill5;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_MageSkill5Pnt;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_SkillDetail;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_SkillShortCut;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Img_SkillShortCut;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_SkillPnt;
	
	// 컨트롤러 이미지
	UPROPERTY()
	TObjectPtr<UTexture2D> Img_Keyboard1;

	UPROPERTY()
	TObjectPtr<UTexture2D> Img_Keyboard2;

	UPROPERTY()
	TObjectPtr<UTexture2D> Img_Keyboard3;

	UPROPERTY()
	TObjectPtr<UTexture2D> Img_Keyboard4;
	
	UPROPERTY()
	TObjectPtr<UTexture2D> Img_Keyboard5;

	UPROPERTY()
	TObjectPtr<UTexture2D> Img_MouseLeftClick;

	UPROPERTY()
	TObjectPtr<UTexture2D> Img_MouseRightClick;

	UPROPERTY()
	FEQSkill EQSkill;
};
