// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetMainUI.h"

#include "EQWidgetInventory.h"
#include "EQWidgetItemActionMenu.h"
#include "Item/EQItemDragDropOperation.h"
#include "Player/EQPlayerController.h"

bool UEQWidgetMainUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                   UDragDropOperation* InOperation)
{
	auto HangItem = Cast<UEQItemDragDropOperation>(InOperation);
	auto MainUI = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI;
	
	if (HangItem->EQSlot->ItemType == EEQItemType::EquippingWeapon || HangItem->EQSlot->ItemType == EEQItemType::EquippingShield)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("현재 장비중인 아이템입니다. 버릴 수 없습니다."));
		MainUI->WBP_EQWidgetInventory->UpdateItemInInventoryUI();
		return true;
	}
	
	MainUI->WBP_EQWidgetItemActionMenu->OnClickBtnDrop();
	MainUI->WBP_EQWidgetInventory->UpdateItemInInventoryUI();
	return true;
}
