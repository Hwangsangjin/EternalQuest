// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemActionMenu.h"

#include "EQWidgetInventory.h"
#include "EQWidgetItemSlot.h"
#include "EQWidgetMainUI.h"
#include "EQWidgetStatus.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Character/EQCharacterPlayer.h"
#include "Component/EQComponentInventory.h"
#include "Component/EQComponentStat.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Item/EQItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EQPlayerController.h"

void UEQWidgetItemActionMenu::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Use->OnHovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnHoverBtnUse);
	Btn_Use->OnUnhovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnUnhoverBtnUse);
	Btn_Use->OnClicked.AddDynamic(this, &UEQWidgetItemActionMenu::OnClickBtnUse);
	Btn_Drop->OnHovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnHoverBtnDrop);
	Btn_Drop->OnUnhovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnUnhoverBtnDrop);
	Btn_Drop->OnClicked.AddDynamic(this, &UEQWidgetItemActionMenu::OnClickBtnDrop);
	Btn_Cancel->OnHovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnHoverBtnCancel);
	Btn_Cancel->OnUnhovered.AddDynamic(this, &UEQWidgetItemActionMenu::OnUnhoverBtnCancel);
	Btn_Cancel->OnClicked.AddDynamic(this, &UEQWidgetItemActionMenu::OnClickBtnCancel);

	auto PC_CastTemp = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController());
	EQComponentInventory = PC_CastTemp->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
}

void UEQWidgetItemActionMenu::BringItemSlotRef(UEQWidgetItemSlot*& InItemSlot)
{
	EQWidgetItemSlot = InItemSlot;
}

void UEQWidgetItemActionMenu::OnHoverBtnUse()
{
	Txt_Use->SetColorAndOpacity(FSlateColor(FColor::Yellow));
}

void UEQWidgetItemActionMenu::OnUnhoverBtnUse()
{
	Txt_Use->SetColorAndOpacity(FSlateColor(FColor::White));
}

void UEQWidgetItemActionMenu::OnClickBtnUse()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	if (EQSlot->ItemType == EEQItemType::Equipment)
	{
		// 장비창을 만들어 스왑해서 옮겨주기
		if (EQSlot->ItemID.RowName.ToString().Contains(TEXT("Wand")) || EQSlot->ItemID.RowName.ToString().Contains(TEXT("Sword")))
		{
			Swap(EQSlot->Quantity, EQComponentInventory->EQAllItem.EquippingSword.Top().Quantity);
			Swap(EQSlot->ItemID.RowName, EQComponentInventory->EQAllItem.EquippingSword.Top().ItemID.RowName);
			Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStatus->UpdateAdditionalStat();
			// EQWidgetInventory->UpdateItemInInventoryUI();
		}
		else if (EQSlot->ItemID.RowName.ToString().Contains(TEXT("Shield")))
		{
			Swap(EQSlot->Quantity, EQComponentInventory->EQAllItem.EquippingShield.Top().Quantity);
			Swap(EQSlot->ItemID.RowName, EQComponentInventory->EQAllItem.EquippingShield.Top().ItemID.RowName);
			Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetStatus->UpdateAdditionalStat();
			// EQWidgetInventory->UpdateItemInInventoryUI();
		}
	}
	else if(EQSlot->ItemType == EEQItemType::Consumtion)
	{
		// 아이템들의 효과 발동하기(회복, 버프 등)
		auto StatComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentStat>();
		auto InventoryWidget = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory;
		auto UseItem = EQSlot->ItemID.DataTable->FindRow<FEQItem>(EQSlot->ItemID.RowName, "");
		
		EQSlot->Quantity--;
		InventoryWidget->UpdateItemInInventoryUI();
		StatComp->SetHp(StatComp->GetCurrentHp() + UseItem->Healing);
	}
	else
	{
		// 재료와 퀘스트 아이템은 사용할 수 없음
	}
	
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory->UpdateItemInInventoryUI();
}

void UEQWidgetItemActionMenu::OnHoverBtnDrop()
{
	Txt_Drop->SetColorAndOpacity(FSlateColor(FColor::Yellow));
}

void UEQWidgetItemActionMenu::OnUnhoverBtnDrop()
{
	Txt_Drop->SetColorAndOpacity(FSlateColor(FColor::White));
}

void UEQWidgetItemActionMenu::OnClickBtnDrop()
{
	// auto Player = GetWorld()->GetFirstPlayerController()->GetCharacter();
	// FTransform SpawnTransform(FRotator(0), FVector(Player->GetActorLocation() + Player->GetActorForwardVector()*100));
	// auto SpawnItem = GetWorld()->SpawnActor<AEQItemBase>(AEQItemBase::StaticClass(), SpawnTransform);
	// SpawnItem->SetItemName(EQSlot->ItemID.RowName, EQSlot->ItemType, EQSlot->Quantity);
	// // ServerRPC_DropItem();
	//
	// int temp = EQSlot->Quantity;
	// for (int i = temp; i > 0 ; i--)
	// {
	// 	EQSlot->Quantity--;
	// }
	// EQSlot->ItemID.RowName = TEXT("");
	EQComponentInventory->DropItem(EQSlot);
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory->
	                                                                   UpdateItemInInventoryUI();
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UEQWidgetItemActionMenu::OnHoverBtnCancel()
{
	Txt_Cancel->SetColorAndOpacity(FSlateColor(FColor::Yellow));
}

void UEQWidgetItemActionMenu::OnUnhoverBtnCancel()
{
	Txt_Cancel->SetColorAndOpacity(FSlateColor(FColor::White));
}

void UEQWidgetItemActionMenu::OnClickBtnCancel()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
