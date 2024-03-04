// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQDamageAmoutUI.h"

#include "Components/TextBlock.h"


void UEQDamageAmoutUI::ShowDamageAmount(float Damage)
{
	Txt_Damage->SetText(FText::FromString(FString::Printf(TEXT("%.f"),Damage)));
	PlayAnimationForward(Fade);
}





