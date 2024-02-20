// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemDropArea.h"

#include "EQWidgetInventory.h"
#include "EQWidgetItemActionMenu.h"
#include "EQWidgetMainUI.h"
#include "Item/EQItemDragDropOperation.h"
#include "Player/EQPlayerController.h"

bool UEQWidgetItemDropArea::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                         UDragDropOperation* InOperation)
{
	// auto HangItem = Cast<UEQItemDragDropOperation>(InOperation);
	// auto MainUI = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI;
	// MainUI->WBP_EQWidgetItemActionMenu->OnClickBtnDrop();
	// MainUI->WBP_EQWidgetInventory->UpdateItemInInventoryUI();
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, TEXT("123"));
	return true;
}
