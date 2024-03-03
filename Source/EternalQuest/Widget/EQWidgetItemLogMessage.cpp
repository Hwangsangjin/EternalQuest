// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemLogMessage.h"

void UEQWidgetItemLogMessage::NativeConstruct()
{
	Super::NativeConstruct();
	SetRenderOpacity(0);
	SetRenderTranslation(FVector2D(0,CurrentTranslationY));
}

void UEQWidgetItemLogMessage::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	CurrTime+=InDeltaTime;
	if (CurrTime > 3.0f)
	{
		CurrentOpacity = FMath::FInterpTo(CurrentOpacity, 0, InDeltaTime, 3);
		SetRenderOpacity(CurrentOpacity);
		CurrentTranslationX = FMath::FInterpTo(CurrentTranslationX, -300, InDeltaTime, 10);
		SetRenderTranslation(FVector2D(CurrentTranslationX, 0));
		if (CurrTime > 4.2f)
		{
			RemoveFromParent();
		}
	}
	else
	{
		CurrentOpacity = FMath::FInterpTo(CurrentOpacity, 1, InDeltaTime, 3);
		CurrentTranslationY = FMath::FInterpTo(CurrentTranslationY, 0, InDeltaTime, 10);
		SetRenderOpacity(CurrentOpacity);
		SetRenderTranslation(FVector2D(0, CurrentTranslationY));
	}
}


