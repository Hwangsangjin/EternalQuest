// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetQuestList.generated.h"

class UTextBlock;
class UButton;
class USizeBox;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetQuestList : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetQuestList(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnClickedQuest1();
	UFUNCTION()
	void OnClickedQuest2();
	UFUNCTION()
	void OnClickedQuest3();
	UFUNCTION()
	void OnClickedQuest4();

	void ClearQuestIcon();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Quest1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Quest2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Quest3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Quest4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_QuestSubject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_QuestDetail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_QuestState;

	bool bOpenQuest1;
	bool bOpenQuest2;
	bool bOpenQuest3;
	bool bOpenQuest4;

	UPROPERTY()
	TObjectPtr<USoundWave> QuestIconClickSound;
};
