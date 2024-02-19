// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentInventory.h"

#include "Struct/EQStructItem.h"
#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Item/EQItemBase.h"
#include "Kismet/KismetSystemLibrary.h"

UEQComponentInventory::UEQComponentInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> DTItemRef(TEXT("/Game/Blueprints/Data/DT_Item.DT_Item"));
	if (DTItemRef.Succeeded())
	{
		ItemID = DTItemRef.Object;
	}
}

void UEQComponentInventory::BeginPlay()
{
	Super::BeginPlay();
	EmptySlot.ItemID.DataTable = ItemID;

	EmptySlot.ItemType = EEQItemType::Equipment;
	for (int i = 0; i < 20; i++) EQAllItem.Equipment.Push(EmptySlot);

	EmptySlot.ItemType = EEQItemType::Consumtion;
	for (int i = 0; i < 20; i++) EQAllItem.Consumtion.Push(EmptySlot);

	EmptySlot.ItemType = EEQItemType::Material;
	for (int i = 0; i < 20; i++) EQAllItem.Material.Push(EmptySlot);

	EmptySlot.ItemType = EEQItemType::Questitem;
	for (int i = 0; i < 20; i++) EQAllItem.QuestItem.Push(EmptySlot);
}

void UEQComponentInventory::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQComponentInventory::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	
}
