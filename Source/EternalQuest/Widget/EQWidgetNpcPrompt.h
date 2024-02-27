// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetNpcPrompt.generated.h"

class UBorder;
class UHorizontalBox;
class AEQCharacterNeutralPlayer;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetNpcPrompt : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void PullNPCInfomation(AEQCharacterNeutralPlayer* InNPC);
	
	UFUNCTION()
	void NextPrompt();
	UFUNCTION()
	void AcceptQuest();
	UFUNCTION()
	void DenyQuest();
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* Txt_NPCName;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* Txt_NPCPrompt;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* Btn_Click;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UHorizontalBox* HorizonBox_Quest;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* Btn_QuestAccept;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* Btn_QuestDeny;
	
	UPROPERTY()
	AEQCharacterNeutralPlayer* NPC;

	UPROPERTY()
	FString DisplayText;

	int32 PromptLast;
	int32 PromptCurrent;
	bool bQuestPromptCond;
	int32 QuestTagIdx;

	void TypeWritingText();
	float CurrentTime;


	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UBorder> Border_Base;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UBorder> Border_NPCName;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UBorder> Border_NPCPrompt;

	float RenderOpacityValue = 0;
};
