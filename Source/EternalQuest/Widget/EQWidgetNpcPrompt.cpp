// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetNpcPrompt.h"

#include "Character/EQCharacterNeutralPlayer.h"
#include "Component/EQComponentInteraction.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"

void UEQWidgetNpcPrompt::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Click->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::NextPrompt);
	Btn_QuestAccept->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::AcceptQuest);
	Btn_QuestDeny->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::DenyQuest);
}

void UEQWidgetNpcPrompt::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	CurrentTime+=InDeltaTime;
	TypeWritingText();
	RenderOpacityValue = FMath::FInterpTo(RenderOpacityValue, 1.0f, InDeltaTime, 4);
	SetRenderOpacity(RenderOpacityValue);
}

void UEQWidgetNpcPrompt::PullNPCInfomation(AEQCharacterNeutralPlayer* InNPC)
{
	RenderOpacityValue = 0;
	SetRenderOpacity(RenderOpacityValue);
	DisplayText = TEXT("");
	Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *DisplayText))); // 읽어주는 동작을 바꾸어야 함.
	NPC = InNPC;
	PromptLast = NPC->NPCPrompt.Num()-1;
	PromptCurrent = 0;

	// NPC 대본 읽기 시작
	Txt_NPCName->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCName)));
	// Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCPrompt[PromptCurrent]))); // 읽어주는 동작을 바꾸어야 함.
}

void UEQWidgetNpcPrompt::NextPrompt()
{
	if (bQuestPromptCond)
	{
		return;
	}
	
	if (PromptLast == PromptCurrent)
	{
		RemoveFromParent();
		GetOwningPlayer()->GetCharacter()->FindComponentByClass<UEQComponentInteraction>()->bCommunicationNPC = true;
		const FInputModeGameOnly InData;
		GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
		return;
	}
	
	DisplayText = TEXT("");
	PromptCurrent++;

	// 퀘스트 로직
	if (NPC->NPCPrompt[PromptCurrent].Contains(TEXT("QuestTag")))
	{
		QuestTagIdx = NPC->NPCPrompt[PromptCurrent].Find(TEXT("QuestTag"));
		NPC->NPCPrompt[PromptCurrent].RemoveAt(QuestTagIdx, 8);
		HorizonBox_Quest->SetVisibility(ESlateVisibility::Visible);
		bQuestPromptCond = true;
		return;
	}
	else
	{
		// Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCPrompt[PromptCurrent])));
		return;
	}

}

void UEQWidgetNpcPrompt::AcceptQuest()
{
	HorizonBox_Quest->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer()->GetCharacter()->FindComponentByClass<UEQComponentInteraction>()->bCommunicationNPC = false;
	RemoveFromParent();
	const FInputModeGameOnly InData;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	NPC->QuestAccepted();
	bQuestPromptCond = false;
}

void UEQWidgetNpcPrompt::DenyQuest()
{
	HorizonBox_Quest->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer()->GetCharacter()->FindComponentByClass<UEQComponentInteraction>()->bCommunicationNPC = false;
	RemoveFromParent();
	const FInputModeGameOnly InData;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	NPC->QuestDenied();
	NPC->NPCPrompt[PromptCurrent].Append(TEXT("QuestTag"), QuestTagIdx);
	bQuestPromptCond = false;
}

void UEQWidgetNpcPrompt::TypeWritingText()
{
	if (DisplayText == *NPC->NPCPrompt[PromptCurrent])
	{
		CurrentTime = 0;
		return;
	}
	
	if (CurrentTime > 0.02f)
	{
		CurrentTime = 0;
		DisplayText = UKismetStringLibrary::GetSubstring(*NPC->NPCPrompt[PromptCurrent], 0, DisplayText.Len() + 1);
		Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *DisplayText))); // 읽어주는 동작을 바꾸어야 함.
	}
	
}
