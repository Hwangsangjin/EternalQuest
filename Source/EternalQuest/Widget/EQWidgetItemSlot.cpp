// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemSlot.h"

#include "EQWidgetDragItem.h"
#include "EQWidgetInventory.h"
#include "EQWidgetItemActionMenu.h"
#include "EQWidgetItemInfo.h"
#include "EQWidgetMainUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Item/EQItemDragDropOperation.h"
#include "Player/EQPlayerController.h"


UEQWidgetItemSlot::UEQWidgetItemSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> EQWidgetDragItemRef(TEXT("/Game/Blueprints/UI/WBP_EQWidgetDragItem.WBP_EQWidgetDragItem_C"));
	if (EQWidgetDragItemRef.Succeeded())
	{
		EQWidgetDragItem = EQWidgetDragItemRef.Class;
	}
	
	DragDropOperation = UEQItemDragDropOperation::StaticClass();

	
}

void UEQWidgetItemSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UEQWidgetItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (EQSlot && EQSlot->Quantity)
	{
		Txt_Quantity->SetText(FText::FromString(FString::Printf(TEXT("%d"), EQSlot->Quantity)));
		auto temp = EQSlot->ItemID.DataTable->FindRow<FEQItem>(EQSlot->ItemID.RowName, "");
		Img_Item->SetBrushFromTexture(temp->Thumbnail);
		Img_Item->SetVisibility(ESlateVisibility::Visible);
		SizeBox_Quantity->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Img_Item->SetVisibility(ESlateVisibility::Hidden);
		SizeBox_Quantity->SetVisibility(ESlateVisibility::Hidden);
	}
	
	EQWidgetInventory = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory;
	EQWidgetItemActionMenu = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetItemActionMenu;
	Btn_Slot->OnHovered.AddDynamic(this, &UEQWidgetItemSlot::OnHoverBtnSlot);
	Btn_Slot->OnUnhovered.AddDynamic(this, &UEQWidgetItemSlot::OnUnhoverBtnSlot);
	Btn_Slot->OnClicked.AddDynamic(this, &UEQWidgetItemSlot::OnClickedBtnSlot);
}

bool UEQWidgetItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	auto HangItem = Cast<UEQItemDragDropOperation>(InOperation);
	
	if (HangItem->EQSlot->ItemType != EEQItemType::Equipment && EQSlot->ItemType == EEQItemType::EquippingWeapon) // 장비 외,->장비창으로 옮길 때
	{
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	if (HangItem->EQSlot->ItemType != EEQItemType::Equipment && EQSlot->ItemType == EEQItemType::EquippingShield) // 장비 외,->장비창으로 옮길 때
	{
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	///////////////////////////////////
	if (HangItem->EQSlot->ItemID.RowName.ToString().Contains(TEXT("Wand")) && EQSlot->ItemType == EEQItemType::EquippingWeapon) // 완드->무기창으로 옮길 떄
	{
		Swap(HangItem->EQWidgetItemSlot->EQSlot->Quantity, EQSlot->Quantity);
		Swap(HangItem->EQWidgetItemSlot->EQSlot->ItemID.RowName, EQSlot->ItemID.RowName);
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	else if (HangItem->EQSlot->ItemID.RowName.ToString().Contains(TEXT("Wand")) && EQSlot->ItemType == EEQItemType::EquippingShield)
	{
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	
	if (HangItem->EQSlot->ItemID.RowName.ToString().Contains(TEXT("Sword")) && EQSlot->ItemType == EEQItemType::EquippingWeapon) // 소드->무기창으로 옮길 떄
	{
		Swap(HangItem->EQWidgetItemSlot->EQSlot->Quantity, EQSlot->Quantity);
		Swap(HangItem->EQWidgetItemSlot->EQSlot->ItemID.RowName, EQSlot->ItemID.RowName);
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	else if (HangItem->EQSlot->ItemID.RowName.ToString().Contains(TEXT("Sword")) && EQSlot->ItemType == EEQItemType::EquippingShield)
	{
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	
	if (HangItem->EQSlot->ItemID.RowName.ToString().Contains(TEXT("Shield")) && EQSlot->ItemType == EEQItemType::EquippingShield) // 방어구->방어구창으로 옮길 떄
	{
		Swap(HangItem->EQWidgetItemSlot->EQSlot->Quantity, EQSlot->Quantity);
		Swap(HangItem->EQWidgetItemSlot->EQSlot->ItemID.RowName, EQSlot->ItemID.RowName);
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	else if (HangItem->EQSlot->ItemID.RowName.ToString().Contains(TEXT("Shield")) && EQSlot->ItemType == EEQItemType::EquippingWeapon)
	{
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	///////////////////////////////////
	if (HangItem->EQSlot->ItemID.RowName == EQSlot->ItemID.RowName) //장비의 이름이 같을 때
	{
		Swap(HangItem->EQSlot->Quantity, EQSlot->Quantity);
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	else // 아닐 때
	{
		Swap(HangItem->EQWidgetItemSlot->EQSlot->Quantity, EQSlot->Quantity);
		Swap(HangItem->EQWidgetItemSlot->EQSlot->ItemID.RowName, EQSlot->ItemID.RowName);
		EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	return true;
}

FReply UEQWidgetItemSlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	
	if (EQSlot->Quantity == 0)
	{
		return FReply::Unhandled();
	}

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton)) // 좌클릭
	{
		auto Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		EQWidgetItemActionMenu->EQSlot = EQSlot;
		return Reply.NativeReply;
	}
	
	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton)) // 우클릭
	{
		auto MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		EQWidgetItemActionMenu->EQSlot = EQSlot;
		EQWidgetItemActionMenu->SizeBox_Base->SetRenderTransform(FWidgetTransform(MousePos, FVector2D(1,1), FVector2D(0), 0));
		EQWidgetItemActionMenu->SetVisibility(ESlateVisibility::Visible);
		return FReply::Handled();
	}
	
	return FReply::Unhandled();
}

void UEQWidgetItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	auto temp = EQSlot->Quantity;
	EQSlot->Quantity = 0;
	EQWidgetInventory->UpdateItemInInventoryUI();
	EQSlot->Quantity = temp;
	auto DragItem = CreateWidget<UEQWidgetDragItem>(GetWorld(), EQWidgetDragItem);
	DragItem->EQSlot = EQSlot;
	auto DragOperator = Cast<UEQItemDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperation));
	DragOperator->EQSlot = EQSlot;
	DragOperator->EQWidgetItemSlot = this;
	DragOperator->DefaultDragVisual = DragItem;
	OutOperation = DragOperator;
}

void UEQWidgetItemSlot::OnHoverBtnSlot()
{
	Border_Item->SetBrushColor(FLinearColor(1,1,1,1));
	Img_HoverTriangle->SetVisibility(ESlateVisibility::Visible);
	EQWidgetInventory->WBP_EQWidgetItemInfo->UpdateItemInfo(*EQSlot);
}

void UEQWidgetItemSlot::OnUnhoverBtnSlot()
{
	Border_Item->SetBrushColor(FLinearColor(1,1,1,0.3));
	Img_HoverTriangle->SetVisibility(ESlateVisibility::Hidden);
}

void UEQWidgetItemSlot::OnClickedBtnSlot()
{
}
