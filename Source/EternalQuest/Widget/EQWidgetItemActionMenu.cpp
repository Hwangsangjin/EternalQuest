// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemActionMenu.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UEQWidgetItemActionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Btn_Use->OnHovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnHoverBtnUse);
	// Btn_Use->OnUnhovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnUnhoverBtnUse);
	// Btn_Drop->OnHovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnHoverBtnDrop);
	// Btn_Drop->OnUnhovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnUnhoverBtnDrop);
	// Btn_Cancel->OnHovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnHoverBtnCancel);
	// Btn_Cancel->OnUnhovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnUnhoverBtnCancel);
}

void UEQWidgetItemActionMenu::OnHoverBtnUse()
{
	Txt_Use->SetColorAndOpacity(FSlateColor(FColor::Yellow));
}

void UEQWidgetItemActionMenu::OnUnhoverBtnUse()
{
	Txt_Use->SetColorAndOpacity(FSlateColor(FColor::White));
}

void UEQWidgetItemActionMenu::OnHoverBtnDrop()
{
	Txt_Use->SetColorAndOpacity(FSlateColor(FColor::Yellow));
}

void UEQWidgetItemActionMenu::OnUnhoverBtnDrop()
{
	Txt_Use->SetColorAndOpacity(FSlateColor(FColor::White));
}

void UEQWidgetItemActionMenu::OnHoverBtnCancel()
{
	Txt_Use->SetColorAndOpacity(FSlateColor(FColor::Yellow));
}

void UEQWidgetItemActionMenu::OnUnhoverBtnCancel()
{
	Txt_Use->SetColorAndOpacity(FSlateColor(FColor::White));
}
