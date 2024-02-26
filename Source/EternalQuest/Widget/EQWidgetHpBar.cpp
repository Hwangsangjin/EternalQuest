// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetHpBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interface/EQInterfaceCharacterWidget.h"

UEQWidgetHpBar::UEQWidgetHpBar(const FObjectInitializer& ObjectInitialzer)
	: Super(ObjectInitialzer)
	, MaxHp(-1)
{
}

void UEQWidgetHpBar::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressBar_Hp = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Hp")));
	ensure(ProgressBar_Hp);

	IEQInterfaceCharacterWidget* CharacterWidget = Cast<IEQInterfaceCharacterWidget>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UEQWidgetHpBar::UpdateHpBar(float NewCurrentHp, float NewMaxHp)
{
	CurrentHp = NewCurrentHp;
	MaxHp = NewMaxHp;

	ensure(MaxHp > 0.0f);
	if (ProgressBar_Hp)
	{
		ProgressBar_Hp->SetPercent(CurrentHp / MaxHp);
	}

	if (TextBlock_Hp)
	{
		TextBlock_Hp->SetText(FText::FromString(GetHpText()));
	}
}

FString UEQWidgetHpBar::GetHpText()
{
	return FString::Printf(TEXT("%.0f/%0.f"), CurrentHp, MaxHp);
}
