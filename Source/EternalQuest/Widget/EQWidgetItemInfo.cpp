// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemInfo.h"

#include "Components/TextBlock.h"

void UEQWidgetItemInfo::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEQWidgetItemInfo::UpdateItemInfo(const FEQSlot& InItem)
{
	auto temp = InItem.ItemID.DataTable->FindRow<FEQItem>(InItem.ItemID.RowName, "");
	if (temp)
	{
		Txt_ItemName->SetText(temp->ItemName);
		Txt_Description->SetText(temp->Description);
	}
	else
	{
		Txt_ItemName->SetText(FText::GetEmpty());
		Txt_Description->SetText(FText::GetEmpty());
	}
}
