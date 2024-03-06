// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetUserName.h"
#include "Components/TextBlock.h"

UEQWidgetUserName::UEQWidgetUserName(const FObjectInitializer& ObjectInitialzer)
	: Super(ObjectInitialzer)
{
}

void UEQWidgetUserName::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEQWidgetUserName::SetUserName(FString InUserName)
{
	TextBlock_UserName->SetText(FText::FromString(InUserName));
}
