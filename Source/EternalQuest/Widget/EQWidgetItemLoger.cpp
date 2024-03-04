// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemLoger.h"

#include "EQWidgetItemLogMessage.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Struct/EQStructEnumBase.h"

UEQWidgetItemLoger::UEQWidgetItemLoger(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UEQWidgetItemLogMessage> ItemLogMessageRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_EQWidgetItemLogMessage.WBP_EQWidgetItemLogMessage_C'"));
	if (ItemLogMessageRef.Succeeded())
	{
		LogMessageFactory = ItemLogMessageRef.Class;
	}
}

void UEQWidgetItemLoger::SetItemLogMessage(const FEQSlot& InSlot)
{
	auto LogMessage = Cast<UEQWidgetItemLogMessage>(CreateWidget(GetWorld(), LogMessageFactory));
	auto FindRowItem = InSlot.ItemID.DataTable->FindRow<FEQItem>(InSlot.ItemID.RowName, "");
	LogMessage->Img_ItemThumbnail->SetBrushFromTexture(FindRowItem->Thumbnail);
	LogMessage->Txt_ItemName->SetText(FindRowItem->ItemName);
	if (FindRowItem->Grade == 0)
	{
		LogMessage->Txt_ItemName->SetColorAndOpacity(FSlateColor(FColor::White));
	}
	else if (FindRowItem->Grade == 1)
	{
		LogMessage->Txt_ItemName->SetColorAndOpacity(FSlateColor(FColor::Turquoise));
	}
	else if (FindRowItem->Grade == 2)
	{
		LogMessage->Txt_ItemName->SetColorAndOpacity(FSlateColor(FColor::Magenta));
	}
	else if (FindRowItem->Grade == 3)
	{
		LogMessage->Txt_ItemName->SetColorAndOpacity(FSlateColor(FColor::Orange));
	}
	LogMessage->Txt_ItemQuantity->SetText(FText::FromString(FString::Printf(TEXT("x%d"), InSlot.Quantity)));
	VerticalBox_Base->AddChild(LogMessage);
}

void UEQWidgetItemLoger::NativeConstruct()
{
	Super::NativeConstruct();
}
