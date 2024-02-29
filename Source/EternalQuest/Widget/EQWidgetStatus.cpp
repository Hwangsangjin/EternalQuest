// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetStatus.h"

#include "Component/EQComponentInventory.h"
#include "Component/EQComponentStat.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Game/EQGameInstance.h"
#include "GameFramework/Character.h"

UEQWidgetStatus::UEQWidgetStatus(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> T_WarriorRef(TEXT("/Game/Assets/StylizedCharactersPack/Common/Texture/T_Warrior_Circle.T_Warrior_Circle"));
	if (T_WarriorRef.Succeeded()) T_Warrior = T_WarriorRef.Object;

	static ConstructorHelpers::FObjectFinder<UTexture2D> T_MageRef(TEXT("/Game/Assets/StylizedCharactersPack/Common/Texture/T_Mage_Circle.T_Mage_Circle"));
	if (T_MageRef.Succeeded()) T_Mage = T_MageRef.Object;
}

void UEQWidgetStatus::NativeConstruct()
{
	Super::NativeConstruct();

	StatComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentStat>();

	if (Cast<UEQGameInstance>(GetWorld()->GetGameInstance())->GetClassType() == EClassType::ECT_Warrior)
	{
		Img_ThumbnailCharacter->SetBrushFromTexture(T_Warrior);
	}
	else if (Cast<UEQGameInstance>(GetWorld()->GetGameInstance())->GetClassType() == EClassType::ECT_Mage)
	{
		Img_ThumbnailCharacter->SetBrushFromTexture(T_Mage);
	}

	Btn_IncreaseHP->OnClicked.AddDynamic(this, &UEQWidgetStatus::OnClickedIncreaseHP);
	Btn_IncreaseMP->OnClicked.AddDynamic(this, &UEQWidgetStatus::OnClickedIncreaseMP);
	Btn_IncreaseSTR->OnClicked.AddDynamic(this, &UEQWidgetStatus::OnClickedIncreaseSTR);
	Btn_IncreaseINT->OnClicked.AddDynamic(this, &UEQWidgetStatus::OnClickedIncreaseINT);
	Btn_IncreaseDEF->OnClicked.AddDynamic(this, &UEQWidgetStatus::OnClickedIncreaseDEF);

	if (StatComp)
	{
		StatComp->OnHpChanged.AddUObject(this, &ThisClass::UpdateState);
	}
	UpdateStatUp();
}

void UEQWidgetStatus::UpdateStatUp()
{
	Txt_StatPoint->SetText(FText::FromString(FString::Printf(TEXT("%d"), StatPoint)));
	if (StatPoint < 1)
	{
		Btn_IncreaseHP->SetVisibility(ESlateVisibility::Hidden);
		Btn_IncreaseMP->SetVisibility(ESlateVisibility::Hidden);
		Btn_IncreaseSTR->SetVisibility(ESlateVisibility::Hidden);
		Btn_IncreaseINT->SetVisibility(ESlateVisibility::Hidden);
		Btn_IncreaseDEF->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Btn_IncreaseHP->SetVisibility(ESlateVisibility::Visible);
		Btn_IncreaseMP->SetVisibility(ESlateVisibility::Visible);
		Btn_IncreaseSTR->SetVisibility(ESlateVisibility::Visible);
		Btn_IncreaseINT->SetVisibility(ESlateVisibility::Visible);
		Btn_IncreaseDEF->SetVisibility(ESlateVisibility::Visible);
	}
}

void UEQWidgetStatus::UpdateState(float InCurrentHP, float InMaxHP) //Delegate
{
	Txt_StateHP->SetText(FText::FromString(FString::Printf(TEXT("HP : %.f / %.f"), InCurrentHP, InMaxHP)));
}

void UEQWidgetStatus::UpdateAdditionalStat()
{
	auto Inventory = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
	
	auto WeaponDataTable = Inventory->EQAllItem.EquippingSword.Top().ItemID.DataTable;
	auto WeaponRowName = Inventory->EQAllItem.EquippingSword.Top().ItemID.RowName;
	auto WeaponItem = WeaponDataTable->FindRow<FEQItem>(WeaponRowName, "");

	auto ShieldDataTable = Inventory->EQAllItem.EquippingShield.Top().ItemID.DataTable;
	auto ShieldRowName = Inventory->EQAllItem.EquippingShield.Top().ItemID.RowName;
	auto ShieldItem = WeaponDataTable->FindRow<FEQItem>(ShieldRowName, "");

	SumMaxHP = 0;
	SumMaxMP = 0;
	SumSTR = 0;
	SumINT = 0;
	SumDEF = 0;
	
	if (WeaponItem)
	{
		SumMaxMP += WeaponItem->MaxMP;
		SumMaxHP += WeaponItem->MaxHP; 
		SumSTR += WeaponItem->STR;
		SumINT += WeaponItem->INT;
		SumDEF += WeaponItem->DEF;
	}

	if (ShieldItem)
	{
		SumMaxHP += ShieldItem->MaxHP;
		SumMaxMP += ShieldItem->MaxMP;
		SumSTR += ShieldItem->STR;
		SumINT += ShieldItem->INT;
		SumDEF += ShieldItem->DEF;
	}
	
	Txt_AdditionalHP->SetText(FText::FromString(FString::Printf(TEXT("+ %.f"), SumMaxHP)));
	Txt_AdditionalMP->SetText(FText::FromString(FString::Printf(TEXT("+ %.f"), SumMaxMP)));
	Txt_AdditionalSTR->SetText(FText::FromString(FString::Printf(TEXT("+ %.f"), SumSTR)));
	Txt_AdditionalINT->SetText(FText::FromString(FString::Printf(TEXT("+ %.f"), SumINT)));
	Txt_AdditionalDEF->SetText(FText::FromString(FString::Printf(TEXT("+ %.f"), SumDEF)));

	if (SumMaxHP) Txt_AdditionalHP->SetColorAndOpacity(FSlateColor(FColor::Green));
	else Txt_AdditionalHP->SetColorAndOpacity(FSlateColor(FColor::White));
	if (SumMaxMP) Txt_AdditionalMP->SetColorAndOpacity(FSlateColor(FColor::Green));
	else Txt_AdditionalMP->SetColorAndOpacity(FSlateColor(FColor::White));
	if (SumSTR) Txt_AdditionalSTR->SetColorAndOpacity(FSlateColor(FColor::Green));
	else Txt_AdditionalSTR->SetColorAndOpacity(FSlateColor(FColor::White));
	if (SumINT) Txt_AdditionalINT->SetColorAndOpacity(FSlateColor(FColor::Green));
	else Txt_AdditionalINT->SetColorAndOpacity(FSlateColor(FColor::White));
	if (SumDEF) Txt_AdditionalDEF->SetColorAndOpacity(FSlateColor(FColor::Green));
	else Txt_AdditionalDEF->SetColorAndOpacity(FSlateColor(FColor::White));
}

void UEQWidgetStatus::OnClickedIncreaseHP()
{
	StatPoint--;
	CurrentPointHP++;
	Prog_HP->SetPercent(CurrentPointHP/MaxPoint);
	Txt_OriginHP->SetText(FText::FromString(FString::Printf(TEXT("%.f"), CurrentPointHP)));
	//
	UpdateStatUp();
}

void UEQWidgetStatus::OnClickedIncreaseMP()
{
	StatPoint--;
	CurrentPointMP++;
	Prog_MP->SetPercent(CurrentPointMP/MaxPoint);
	Txt_OriginMP->SetText(FText::FromString(FString::Printf(TEXT("%.f"), CurrentPointMP)));
	//
	UpdateStatUp();
}

void UEQWidgetStatus::OnClickedIncreaseSTR()
{
	StatPoint--;
	CurrentPointSTR++;
	Prog_STR->SetPercent(CurrentPointSTR/MaxPoint);
	Txt_OriginSTR->SetText(FText::FromString(FString::Printf(TEXT("%.f"), CurrentPointSTR)));
	//
	UpdateStatUp();
}

void UEQWidgetStatus::OnClickedIncreaseINT()
{
	StatPoint--;
	CurrentPointINT++;
	Prog_INT->SetPercent(CurrentPointINT/MaxPoint);
	Txt_OriginINT->SetText(FText::FromString(FString::Printf(TEXT("%.f"), CurrentPointINT)));

	//
	UpdateStatUp();
}

void UEQWidgetStatus::OnClickedIncreaseDEF()
{
	StatPoint--;
	CurrentPointDEF++;
	Prog_DEF->SetPercent(CurrentPointDEF/MaxPoint);
	Txt_OriginDEF->SetText(FText::FromString(FString::Printf(TEXT("%.f"), CurrentPointDEF)));
	//
	UpdateStatUp();
}
