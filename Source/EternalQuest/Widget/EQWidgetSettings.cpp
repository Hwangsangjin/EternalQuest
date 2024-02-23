// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetSettings.h"

#include "EQWidgetMainUI.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/EQPlayerController.h"

void UEQWidgetSettings::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Settings->OnClicked.AddDynamic(this, &UEQWidgetSettings::OnClickedSetting);
	Btn_Exit->OnClicked.AddDynamic(this, &UEQWidgetSettings::OnClickedExit);
	Btn_Cancel->OnClicked.AddDynamic(this, &UEQWidgetSettings::OnClickedCancel);
}

void UEQWidgetSettings::OnClickedSetting()
{
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSettings->SetVisibility(ESlateVisibility::Hidden);
}

void UEQWidgetSettings::OnClickedExit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UEQWidgetSettings::OnClickedCancel()
{
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetSettings->SetVisibility(ESlateVisibility::Hidden);
}
