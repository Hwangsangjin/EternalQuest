// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemActionMenu.h"

#include "EQWidgetInventory.h"
#include "EQWidgetItemSlot.h"
#include "EQWidgetMainUI.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Character/EQCharacterPlayer.h"
#include "Component/EQComponentInventory.h"
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
	}
	else if(EQSlot->ItemType == EEQItemType::Consumtion)
	{
		// 아이템들의 효과 발동하기(회복, 버프 등)
		EQSlot->Quantity--;
		EQSlot->ItemID.RowName = TEXT("");	
	}
	else
	{
		// 재료와 퀘스트 아이템은 사용할 수 없음
	}


	
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory->
																	   UpdateItemInInventoryUI();
}

void UEQWidgetItemActionMenu::OnHoverBtnDrop()
{
	Txt_Drop->SetColorAndOpacity(FSlateColor(FColor::Yellow));
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, FString::Printf(TEXT("%p"), &EQWidgetItemSlot));
}

void UEQWidgetItemActionMenu::OnUnhoverBtnDrop()
{
	Txt_Drop->SetColorAndOpacity(FSlateColor(FColor::White));
}

void UEQWidgetItemActionMenu::OnClickBtnDrop()
{
	auto Player = GetWorld()->GetFirstPlayerController()->GetCharacter();
	FTransform SpawnTransform(FRotator(0), FVector(Player->GetActorLocation() + Player->GetActorForwardVector()*100));
	auto Item = Cast<AEQItemBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AEQItemBase::StaticClass(), SpawnTransform));
	if (Item)
	{
		Item->ItemName.RowName = EQSlot->ItemID.RowName;
		Item->ItemQuantity = EQSlot->Quantity;
		Item->ItemType = EQSlot->ItemType;
		UGameplayStatics::FinishSpawningActor(Item, SpawnTransform);
	}
	
	// EQSlot->Quantity--;
	int temp = EQSlot->Quantity;
	for (int i = temp; i > 0 ; i--)
	{
		EQSlot->Quantity--;
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, TEXT("ext"));
	}
	EQSlot->ItemID.RowName = TEXT("");
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
