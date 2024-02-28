// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetItemInfo.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Item/EQItemPreview.h"
#include "Kismet/GameplayStatics.h"

UEQWidgetItemInfo::UEQWidgetItemInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AActor> ItemPreviewFactoryRef(TEXT("/Game/Blueprints/Item/BP_ItemPreview.BP_ItemPreview_C"));
	if (ItemPreviewFactoryRef.Succeeded()) ItemPreviewFactory = ItemPreviewFactoryRef.Class;
}

void UEQWidgetItemInfo::NativeConstruct()
{
	Super::NativeConstruct();
	ItemPreview = Cast<AEQItemPreview>(UGameplayStatics::GetActorOfClass(GetWorld(), ItemPreviewFactory));
}

void UEQWidgetItemInfo::UpdateItemInfo(const FEQSlot& InItem)
{
	auto temp = InItem.ItemID.DataTable->FindRow<FEQItem>(InItem.ItemID.RowName, "");
	if (temp)
	{
		if (temp->Grade == 0) Txt_ItemName->SetColorAndOpacity(FSlateColor(FColor::White));
		else if (temp->Grade == 1) Txt_ItemName->SetColorAndOpacity(FSlateColor(FColor::Turquoise));
		else if (temp->Grade == 2) Txt_ItemName->SetColorAndOpacity(FSlateColor(FColor::Magenta));
		else if (temp->Grade == 3) Txt_ItemName->SetColorAndOpacity(FSlateColor(FColor::Orange));
		Txt_ItemName->SetText(temp->ItemName);
		
		Txt_Description->SetText(temp->Description);
		
		Txt_IncreaseHP->SetText(FText::FromString(FString::Printf(TEXT("%.f"), temp->MaxHP)));
		if (temp->MaxHP == 0) Txt_IncreaseHP->SetColorAndOpacity(FSlateColor(FColor::White));
		else Txt_IncreaseHP->SetColorAndOpacity(FSlateColor(FColor::Green));
		
		Txt_IncreaseMP->SetText(FText::FromString(FString::Printf(TEXT("%.f"), temp->MaxMP)));
		if (temp->MaxMP == 0) Txt_IncreaseMP->SetColorAndOpacity(FSlateColor(FColor::White));
		else Txt_IncreaseMP->SetColorAndOpacity(FSlateColor(FColor::Green));
		
		Txt_IncreaseSTR->SetText(FText::FromString(FString::Printf(TEXT("%.f"), temp->STR)));
		if (temp->STR == 0) Txt_IncreaseSTR->SetColorAndOpacity(FSlateColor(FColor::White));
		else Txt_IncreaseSTR->SetColorAndOpacity(FSlateColor(FColor::Green));
		
		Txt_IncreaseINT->SetText(FText::FromString(FString::Printf(TEXT("%.f"), temp->INT)));
		if (temp->INT == 0) Txt_IncreaseINT->SetColorAndOpacity(FSlateColor(FColor::White));
		else Txt_IncreaseINT->SetColorAndOpacity(FSlateColor(FColor::Green));
		
		Txt_IncreaseDEF->SetText(FText::FromString(FString::Printf(TEXT("%.f"), temp->DEF)));
		if (temp->DEF == 0) Txt_IncreaseDEF->SetColorAndOpacity(FSlateColor(FColor::White));
		else Txt_IncreaseDEF->SetColorAndOpacity(FSlateColor(FColor::Green));
		
		ItemPreview->MeshComp->SetStaticMesh(temp->Mesh);
		Img_RenderItem->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Txt_ItemName->SetText(FText::GetEmpty());
		Txt_Description->SetText(FText::GetEmpty());
		Txt_IncreaseHP->SetText(FText::GetEmpty());
		Txt_IncreaseMP->SetText(FText::GetEmpty());
		Txt_IncreaseSTR->SetText(FText::GetEmpty());
		Txt_IncreaseINT->SetText(FText::GetEmpty());
		Txt_IncreaseDEF->SetText(FText::GetEmpty());
		Img_RenderItem->SetVisibility(ESlateVisibility::Hidden);
	}
}
