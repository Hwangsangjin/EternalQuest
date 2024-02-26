// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetChattingSystem.h"

#include "EQWidgetChatMessage.h"
#include "EQWidgetMainUI.h"
#include "Character/EQCharacterPlayer.h"
#include "Component/EQComponentMove.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "GameFramework/PlayerState.h"
#include "Player/EQPlayerController.h"

UEQWidgetChattingSystem::UEQWidgetChattingSystem(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UEQWidgetChattingSystem::NativeConstruct()
{
	Super::NativeConstruct();
	EditText_ChatInput->OnTextCommitted.AddDynamic(this,&ThisClass::OnTextCommittedChat);
}

void UEQWidgetChattingSystem::OnTextCommittedChat(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (Text.IsEmpty())
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
		return;
	}
	if (CommitMethod == ETextCommit::OnEnter)
	{
		auto MyEQChatWidget = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetChattingSystem;
		// MyEQChatWidget->UpdateChat(Text, FText::FromString(MyEQChatWidget->GetOwningPlayerState()->GetPlayerName()));
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentMove>()->ServerRPC_SendChat(Text,
FText::FromString(MyEQChatWidget->GetOwningPlayerState()->GetPlayerName()));
		MyEQChatWidget->EditText_ChatInput->SetText(FText::GetEmpty());
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	}
}

void UEQWidgetChattingSystem::UpdateChat(const FText& InText, const FText& InPlayerName)
{
	auto ChatMessage = CreateWidget(GetWorld(), ChatMessageFactory);
	auto InChatMessage = Cast<UEQWidgetChatMessage>(ChatMessage);
	InChatMessage->PlayerName = InPlayerName;
	InChatMessage->ChatDetail = InText;
	ScrBox_ChatList->AddChild(InChatMessage);
	ScrBox_ChatList->ScrollToEnd();
}