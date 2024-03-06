// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetNpcPrompt.h"

#include "EQWidgetChattingSystem.h"
#include "EQWidgetMainUI.h"
#include "Character/EQCharacterNeutralPlayer.h"
#include "Component/EQComponentInteraction.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "Player/EQPlayerController.h"

void UEQWidgetNpcPrompt::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_Click->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::NextPrompt);
	Btn_QuestAccept->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::AcceptQuest);
	Btn_QuestDeny->OnClicked.AddDynamic(this, &UEQWidgetNpcPrompt::DenyQuest);

	PC = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController());
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
	// 모든 UI 없애기 //
	PC->EQWidgetMainUI->SetVisibility(ESlateVisibility::Hidden);
	
	// UI 연출
	RenderOpacityValue = 0;
	SetRenderOpacity(RenderOpacityValue);
	DisplayText = TEXT("");
	Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *DisplayText)));
	// UI 연출
	
	NPC = InNPC;

	// NPC 퀘스트를 클리어했는지 점검하기
	NPC->QuestSuccess();

	// NPC 대사 길이 확인
	PromptLast = NPC->NPCPrompt.Num()-1;
	PromptCurrent = 0;

	// NPC 대본 읽기 시작
	Txt_NPCName->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCName)));
	// Txt_NPCPrompt->SetText(FText::FromString(FString::Printf(TEXT("%s"), *NPC->NPCPrompt[PromptCurrent]))); // 읽어주는 동작을 바꾸어야 함.
}

void UEQWidgetNpcPrompt::NextPrompt()
{
	if (bQuestPromptCond) // 퀘스트 창이 떴을 때 클릭으로 스킵되는 현상을 막아줌
	{
		return;
	}
	
	if (PromptLast == PromptCurrent) // 마지막 대사 후 클릭할 때 창을 사라지게 함.
	{
		RemoveFromParent();
		GetOwningPlayer()->GetCharacter()->FindComponentByClass<UEQComponentInteraction>()->bCommunicationNPC = false;
		const FInputModeGameOnly InData;
		GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->SetVisibility(ESlateVisibility::Visible);
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
}

void UEQWidgetNpcPrompt::AcceptQuest()
{
	HorizonBox_Quest->SetVisibility(ESlateVisibility::Hidden);
	PC->EQWidgetMainUI->SetVisibility(ESlateVisibility::Visible);
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
	PC->EQWidgetMainUI->SetVisibility(ESlateVisibility::Visible);
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
