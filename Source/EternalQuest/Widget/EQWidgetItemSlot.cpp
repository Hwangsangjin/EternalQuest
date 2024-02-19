// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemSlot.h"

#include "EQWidgetInventory.h"
#include "EQWidgetItemActionMenu.h"
#include "EQWidgetItemInfo.h"
#include "EQWidgetMainUI.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Player/EQPlayerController.h"

UEQWidgetItemSlot::UEQWidgetItemSlot(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemRef(TEXT("/Game/Blueprints/Data/DT_Item.DT_Item"));
	if (DT_ItemRef.Succeeded())
	{
		EQSlot.ItemID.DataTable = DT_ItemRef.Object;
	}
}

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
	EQWidgetInventory = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetInventory;
	EQWidgetActionMenu = UEQWidgetItemActionMenu::StaticClass();
	Btn_Slot->OnHovered.AddDynamic(this, &UEQWidgetItemSlot::OnHoverBtnSlot);
	Btn_Slot->OnUnhovered.AddDynamic(this, &UEQWidgetItemSlot::OnUnhoverBtnSlot);
}

FReply UEQWidgetItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		auto temp = CreateWidget<UEQWidgetItemActionMenu>(GetWorld(),EQWidgetActionMenu);
		temp->AddToViewport();
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, TEXT("Right Button"));
		return FReply::Handled();
	}
	return FReply::Unhandled();
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
