// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetChatMessage.h"

#include "Components/TextBlock.h"

void UEQWidgetChatMessage::NativeConstruct()
{
	Super::NativeConstruct();
	Txt_PlayerName->SetText(PlayerName);
	Txt_ChatDetail->SetText(ChatDetail);
}
