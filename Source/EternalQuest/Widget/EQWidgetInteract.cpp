// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetInteract.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UEQWidgetInteract::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEQWidgetInteract::InteractShowItem()
{
	Txt_InputKey->SetText(FText::FromString(TEXT("F")));
	Txt_Detail->SetText(FText::FromString(TEXT("획득")));
	SizeBox_Switch->SetVisibility(ESlateVisibility::Visible);
}

void UEQWidgetInteract::InteractShowNPC()
{
	Txt_InputKey->SetText(FText::FromString(TEXT("E")));
	Txt_Detail->SetText(FText::FromString(TEXT("대화")));
	SizeBox_Switch->SetVisibility(ESlateVisibility::Visible);
}

void UEQWidgetInteract::InteractDisable()
{
	SizeBox_Switch->SetVisibility(ESlateVisibility::Hidden);
}
