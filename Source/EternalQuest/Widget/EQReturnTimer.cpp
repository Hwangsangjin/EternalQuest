// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQReturnTimer.h"

#include "Components/TextBlock.h"

void UEQReturnTimer::CountToReturn(int32 Count)
{
	UE_LOG(LogTemp,Warning,TEXT("CountToReturn"));
	txt_Num -> SetText(FText::FromString(FString::Printf(TEXT("%d"),Count)));
}
