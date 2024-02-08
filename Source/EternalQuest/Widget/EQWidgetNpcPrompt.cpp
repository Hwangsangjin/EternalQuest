// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetNpcPrompt.h"

#include "Character/EQCharacterNeutralPlayer.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

void UEQWidgetNpcPrompt::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Click->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::NextPrompt);
	Btn_QuestAccept->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::AcceptQuest);
	Btn_QuestDeny->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::DenyQuest);
}

void UEQWidgetNpcPrompt::PullNPCInfomation(AEQCharacterNeutralPlayer* InNPC)
{
	NPC = InNPC;
	PromptLast = NPC->NPCPrompt.Num()-1;
	PromptCurrent = 0;
	Txt_NPCName->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCName)));
	Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCPrompt[PromptCurrent])));
}

void UEQWidgetNpcPrompt::NextPrompt()
{
	if (PromptLast == PromptCurrent)
	{
		RemoveFromParent();
		const FInputModeGameOnly InData;
		GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
		return;
	}
	
	PromptCurrent++;

	// 퀘스트 로직
	if (NPC->NPCPrompt[PromptCurrent].Contains(TEXT("QuestTag")))
	{
		auto temp = NPC->NPCPrompt[PromptCurrent].Find(TEXT("QuestTag"));
		HorizonBox_Quest->SetVisibility(ESlateVisibility::Visible);
		NPC->NPCPrompt[PromptCurrent].RemoveAt(temp, 8);
		Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCPrompt[PromptCurrent])));
		return;
	}
	
	Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCPrompt[PromptCurrent])));
}

void UEQWidgetNpcPrompt::AcceptQuest()
{
	HorizonBox_Quest->SetVisibility(ESlateVisibility::Hidden);
	RemoveFromParent();
	const FInputModeGameOnly InData;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	NPC->QuestAccepted();
}

void UEQWidgetNpcPrompt::DenyQuest()
{
	HorizonBox_Quest->SetVisibility(ESlateVisibility::Hidden);
	RemoveFromParent();
	const FInputModeGameOnly InData;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	NPC->QuestDenied();
}
