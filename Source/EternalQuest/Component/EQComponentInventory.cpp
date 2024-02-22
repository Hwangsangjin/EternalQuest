// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentInventory.h"

#include "Character/EQCharacterPlayer.h"
#include "Item/EQItemBase.h"
#include "Net/UnrealNetwork.h"

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
	DropRowName = InSlot->ItemID.RowName;
	DropItemType = InSlot->ItemType;
	DropQuantity = InSlot->Quantity;
	MyPlayer = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (GetOwner()->HasAuthority())
	{
		FTransform SpawnTransform(FRotator(0),
						  FVector(MyPlayer->GetActorLocation() + MyPlayer->GetActorForwardVector() * 100));
		// CurrItem = GetWorld()->SpawnActor<AEQItemBase>(ItemFactory, SpawnTransform);
		CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(ItemFactory, SpawnTransform);
		if (CurrItem)
		{
			CurrItem->ItemName.RowName = DropRowName;
			CurrItem->ItemType = DropItemType;
			CurrItem->ItemQuantity = DropQuantity;
			CurrItem->FinishSpawning(SpawnTransform);
		}
		// OnRep_SetItem();
		CurrItem->SetItemName(DropRowName, DropItemType, DropQuantity);
	}
	else
	{
		ServerRPC_DropItem(DropRowName, DropItemType, DropQuantity, MyPlayer);
	}
	
	int temp = InSlot->Quantity;
	for (int i = temp; i > 0; i--)
	{
		InSlot->Quantity--;
	}
	InSlot->ItemID.RowName = TEXT("");
}

void UEQComponentInventory::OnRep_SetItem()
{
	CurrItem->ItemName.RowName = DropRowName;
	CurrItem->ItemType = DropItemType;
	CurrItem->ItemQuantity = DropQuantity;
	CurrItem->SetItemName(DropRowName, DropItemType, DropQuantity);
}

void UEQComponentInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UEQComponentInventory, CurrItem)
	DOREPLIFETIME(UEQComponentInventory, DropRowName)
	DOREPLIFETIME(UEQComponentInventory, DropItemType)
	DOREPLIFETIME(UEQComponentInventory, DropQuantity)

}

void UEQComponentInventory::ClientRPC_DropItem_Implementation(const FName& RowName, const EEQItemType& ItemType,
                                                             const int32& Quantity,
                                                             const FTransform& InTransform)
{
	if (CurrItem)
	{
		CurrItem->SetItemName(RowName,ItemType,Quantity);
	}
}

void UEQComponentInventory::ServerRPC_DropItem_Implementation(const FName& RowName, const EEQItemType& ItemType,
                                                              const int32& Quantity,
                                                              AEQCharacterPlayer* InPlayer)
{
	FTransform SpawnTransform(FRotator(0),
	                          FVector(InPlayer->GetActorLocation() + InPlayer->GetActorForwardVector() * 100));
	// CurrItem = GetWorld()->SpawnActor<AEQItemBase>(ItemFactory, SpawnTransform);
	CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(ItemFactory, SpawnTransform);
	if (CurrItem)
	{
		CurrItem->ItemName.RowName = RowName;
		CurrItem->ItemType = ItemType;
		CurrItem->ItemQuantity = Quantity;
		CurrItem->FinishSpawning(SpawnTransform);
	}
	ClientRPC_DropItem(RowName, ItemType, Quantity, SpawnTransform);
}
