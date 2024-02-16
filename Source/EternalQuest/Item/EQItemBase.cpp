// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EQItemBase.h"


// Sets default values
AEQItemBase::AEQItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(MeshComp);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Ref(TEXT("/Game/LDJ/DataTable/DT_Item.DT_Item"));
	if (DT_Ref.Succeeded())
	{
		ItemDataTable = DT_Ref.Object;
		Slot.ItemID.DataTable = ItemDataTable;
	}
}

void AEQItemBase::BeginPlay()
{
	Super::BeginPlay();
	SetItemName(ItemName.RowName, ItemType, ItemQuantity);
}

void AEQItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEQItemBase::SetItemName(const FName& InName, EEQItemType InType, const int32& Qunatity)
{
	Slot.ItemID.RowName = InName;
	Slot.Quantity = Qunatity;
	Slot.ItemType = InType;
	auto temp = ItemDataTable->FindRow<FEQItem>(Slot.ItemID.RowName, "");
	MeshComp->SetStaticMesh(temp->Mesh);
}