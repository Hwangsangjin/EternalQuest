// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetInventory.h"

#include "Components/SizeBox.h"

void UEQWidgetInventory::OpenCloseInventoryWidget()
{
	if (bVisibilityFlag)
	{
		bVisibilityFlag = false;
		SizeBox_Base->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		bVisibilityFlag = true;
		SizeBox_Base->SetVisibility(ESlateVisibility::Visible);
	}
}
