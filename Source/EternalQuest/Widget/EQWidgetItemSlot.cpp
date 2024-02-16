// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemSlot.h"

#include "EQWidgetInventory.h"
#include "EQWidgetItemInfo.h"
#include "EQWidgetMainUI.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Player/EQPlayerController.h"

void UEQWidgetItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (EQSlot.Quantity)
	{
		Txt_Quantity->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSlot.Quantity)));
		auto temp = EQSlot.ItemID.DataTable->FindRow<FEQItem>(EQSlot.ItemID.RowName, "");
		Img_Item->SetBrushFromTexture(temp->Thumbnail);
		Img_Item->SetVisibility(ESlateVisibility::Visible);
		SizeBox_Quantity->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Img_Item->SetVisibility(ESlateVisibility::Hidden);
		SizeBox_Quantity->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UEQWidgetItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Slot->OnHovered.AddDynamic(this, &UEQWidgetItemSlot::OnHoverBtnSlot);
	Btn_Slot->OnUnhovered.AddDynamic(this, &UEQWidgetItemSlot::OnUnhoverBtnSlot);
	EQWidgetInventory = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory;
}

void UEQWidgetItemSlot::OnHoverBtnSlot()
{
	Border_Item->SetBrushColor(FLinearColor(1,1,1,1));
	Img_HoverTriangle->SetVisibility(ESlateVisibility::Visible);
	EQWidgetInventory->WBP_EQWidgetItemInfo->UpdateItemInfo(EQSlot);
}

void UEQWidgetItemSlot::OnUnhoverBtnSlot()
{
	Border_Item->SetBrushColor(FLinearColor(1,1,1,0.3));
	Img_HoverTriangle->SetVisibility(ESlateVisibility::Hidden);
}
