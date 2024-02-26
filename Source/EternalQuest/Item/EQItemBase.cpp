// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EQItemBase.h"

#include "Net/UnrealNetwork.h"
#include "Player/EQPlayerController.h"

// Sets default values
AEQItemBase::AEQItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(MeshComp);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Ref(TEXT("/Game/Assets/Cute_Little_Animals/Tree_And_Box/Mesh/SM_Box.SM_Box"));
	if (SM_Ref.Succeeded())
	{
		StaticMesh = SM_Ref.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Ref(TEXT("/Game/Blueprints/Data/DT_Item.DT_Item"));
	if (DT_Ref.Succeeded())
	{
		ItemDataTable = DT_Ref.Object;
		Slot.ItemID.DataTable = ItemDataTable;
	}
	
	bReplicates = true;
}

void AEQItemBase::PostNetInit()
{
	Super::PostNetInit();
	SetOwner(GetWorld()->GetFirstPlayerController());
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
	if (temp)
	{
		MeshComp->SetStaticMesh(temp->Mesh);
	}
}

void AEQItemBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEQItemBase, Slot)
	DOREPLIFETIME(AEQItemBase, ItemName)
	DOREPLIFETIME(AEQItemBase, ItemType)
	DOREPLIFETIME(AEQItemBase, ItemQuantity)
}
