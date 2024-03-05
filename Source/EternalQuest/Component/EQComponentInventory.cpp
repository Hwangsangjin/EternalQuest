// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentInventory.h"

#include "EngineUtils.h"
#include "Character/EQCharacterPlayer.h"
#include "Item/EQItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/EQPlayerController.h"
#include "Save/EQSaveGame.h"

UEQComponentInventory::UEQComponentInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> DTItemRef(TEXT("/Game/Blueprints/Data/DT_Item.DT_Item"));
	if (DTItemRef.Succeeded())
	{
		ItemID = DTItemRef.Object;
	}
	static ConstructorHelpers::FClassFinder<AEQItemBase>
		ItemFacRef(TEXT("/Game/Blueprints/Item/BP_EQItem.BP_EQItem_C"));
	if (ItemFacRef.Succeeded())
	{
		ItemFactory = ItemFacRef.Class;
	}
}

void UEQComponentInventory::BeginPlay()
{
	Super::BeginPlay();
	LoadInventory();
	if (EQAllItem.IsEmpty())
	{
		EmptySlot.ItemID.DataTable = ItemID;
	
		EmptySlot.ItemType = EEQItemType::Equipment;
		for (int i = 0; i < 20; i++) EQAllItem.Equipment.Push(EmptySlot);

		EmptySlot.ItemType = EEQItemType::Consumtion;
		for (int i = 0; i < 20; i++) EQAllItem.Consumtion.Push(EmptySlot);

		EmptySlot.ItemType = EEQItemType::Material;
		for (int i = 0; i < 20; i++) EQAllItem.Material.Push(EmptySlot);

		EmptySlot.ItemType = EEQItemType::Questitem;
		for (int i = 0; i < 20; i++) EQAllItem.QuestItem.Push(EmptySlot);
	
		EmptySlot.ItemType = EEQItemType::EquippingWeapon;
		for (int i = 0; i < 1; i++) EQAllItem.EquippingSword.Push(EmptySlot);

		EmptySlot.ItemType = EEQItemType::EquippingShield;
		for (int i = 0; i < 1; i++) EQAllItem.EquippingShield.Push(EmptySlot);
	}
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

bool UEQComponentInventory::AddToInventory(const FEQSlot& InSlot)
{
	if (InSlot.ItemType == EEQItemType::Equipment)
	{
		for (int i = 0; i < EQAllItem.Equipment.Num(); i++)
		{
			if (InSlot.ItemID.RowName == EQAllItem.Equipment[i].ItemID.RowName)
			{
				auto OutRow = InSlot.ItemID.DataTable->FindRow<FEQItem>(InSlot.ItemID.RowName, "");
				if (OutRow->StackSize >= (InSlot.Quantity + EQAllItem.Equipment[i].Quantity))
				{
					EQAllItem.Equipment[i].Quantity = (InSlot.Quantity + EQAllItem.Equipment[i].Quantity);
					return true;
				}
			}
		}

		for (int i = 0; i < EQAllItem.Equipment.Num(); i++)
		{
			if (EQAllItem.Equipment[i].Quantity == 0)
			{
				EQAllItem.Equipment[i] = InSlot;
				return true;
			}
		}
		return false;
	}

	else if (InSlot.ItemType == EEQItemType::Consumtion)
	{
		for (int i = 0; i < EQAllItem.Consumtion.Num(); i++)
		{
			if (InSlot.ItemID.RowName == EQAllItem.Consumtion[i].ItemID.RowName)
			{
				auto OutRow = InSlot.ItemID.DataTable->FindRow<FEQItem>(InSlot.ItemID.RowName, "");
				if (OutRow->StackSize >= (InSlot.Quantity + EQAllItem.Consumtion[i].Quantity))
				{
					EQAllItem.Consumtion[i].Quantity = (InSlot.Quantity + EQAllItem.Consumtion[i].Quantity);
					return true;
				}
			}
		}

		for (int i = 0; i < EQAllItem.Consumtion.Num(); i++)
		{
			if (EQAllItem.Consumtion[i].Quantity == 0)
			{
				EQAllItem.Consumtion[i] = InSlot;
				return true;
			}
		}

		return false;
	}
	else if (InSlot.ItemType == EEQItemType::Material)
	{
		for (int i = 0; i < EQAllItem.Material.Num(); i++)
		{
			if (InSlot.ItemID.RowName == EQAllItem.Material[i].ItemID.RowName)
			{
				auto OutRow = InSlot.ItemID.DataTable->FindRow<FEQItem>(InSlot.ItemID.RowName, "");
				if (OutRow->StackSize >= (InSlot.Quantity + EQAllItem.Material[i].Quantity))
				{
					EQAllItem.Material[i].Quantity = (InSlot.Quantity + EQAllItem.Material[i].Quantity);
					return true;
				}
			}
		}

		for (int i = 0; i < EQAllItem.Material.Num(); i++)
		{
			if (EQAllItem.Material[i].Quantity == 0)
			{
				EQAllItem.Material[i] = InSlot;
				return true;
			}
		}

		return false;
	}
	else if (InSlot.ItemType == EEQItemType::Questitem)
	{
		for (int i = 0; i < EQAllItem.QuestItem.Num(); i++)
		{
			if (InSlot.ItemID.RowName == EQAllItem.QuestItem[i].ItemID.RowName)
			{
				auto OutRow = InSlot.ItemID.DataTable->FindRow<FEQItem>(InSlot.ItemID.RowName, "");
				if (OutRow->StackSize >= (InSlot.Quantity + EQAllItem.QuestItem[i].Quantity))
				{
					EQAllItem.QuestItem[i].Quantity = (InSlot.Quantity + EQAllItem.QuestItem[i].Quantity);
					return true;
				}
			}
		}

		for (int i = 0; i < EQAllItem.QuestItem.Num(); i++)
		{
			if (EQAllItem.QuestItem[i].Quantity == 0)
			{
				EQAllItem.QuestItem[i] = InSlot;
				return true;
			}
		}
		return false;
	}
	
	return false;
}

void UEQComponentInventory::DropItem(FEQSlot* InSlot)
{
	if (InSlot->ItemType == EEQItemType::EquippingWeapon || InSlot->ItemType == EEQItemType::EquippingShield)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("현재 장비중인 아이템입니다. 버릴 수 없습니다."));
		return;
	}
	auto InPlayer = GetWorld()->GetFirstPlayerController()->GetCharacter();
	FTransform SpawnTransform(FRotator(0),
							  FVector(InPlayer->GetActorLocation() + InPlayer->GetActorForwardVector() * 100));
	ServerRPC_DropItem(InSlot->ItemID.RowName, InSlot->ItemType, InSlot->Quantity, SpawnTransform);
	
	int temp = InSlot->Quantity;
	for (int i = temp; i > 0; i--)
	{
		InSlot->Quantity--;
	}
	InSlot->ItemID.RowName = TEXT("");
}

void UEQComponentInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEQComponentInventory, CurrItem)
}

void UEQComponentInventory::SaveInventory()
{
	UEQSaveGame* SaveGameInstance = Cast<UEQSaveGame>(UGameplayStatics::CreateSaveGameObject(UEQSaveGame::StaticClass()));
	SaveGameInstance->EQAllItem = EQAllItem;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "EQSlot", 0);
}

void UEQComponentInventory::LoadInventory()
{
	UEQSaveGame* SaveGameInstance = Cast<UEQSaveGame>(UGameplayStatics::CreateSaveGameObject(UEQSaveGame::StaticClass()));
	SaveGameInstance = Cast<UEQSaveGame>(UGameplayStatics::LoadGameFromSlot("EQSlot", 0));
	if (SaveGameInstance)
	{
		EQAllItem = SaveGameInstance->EQAllItem;
	}
}

void UEQComponentInventory::ClientRPC_DropItem_Implementation(const FName& RowName, const EEQItemType& ItemType,
                                                              const int32& Quantity)
{
}

void UEQComponentInventory::ServerRPC_DropItem_Implementation(const FName& RowName, const EEQItemType& ItemType,
                                                              const int32& Quantity, const FTransform& ItemLoc)
{
	CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(ItemFactory, ItemLoc);
	if (CurrItem)
	{
		CurrItem->ItemName.RowName = RowName;
		CurrItem->ItemType = ItemType;
		CurrItem->ItemQuantity = Quantity;
	}
	CurrItem->FinishSpawning(ItemLoc);
	
	for (auto e : TActorRange<AEQPlayerController>(GetWorld()))
	{
	}
}
