// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetDragItem.h"

#include "EQWidgetMainUI.h"
#include "Components/Image.h"
#include "Player/EQPlayerController.h"
#include "Struct/EQStructEnumBase.h"

void UEQWidgetDragItem::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UEQWidgetDragItem::NativeConstruct()
{
	Super::NativeConstruct();
	auto StructTemp = EQSlot->ItemID.DataTable->FindRow<FEQItem>(EQSlot->ItemID.RowName, "");
	Img_Thumbnail->SetBrushFromTexture(StructTemp->Thumbnail);
}
