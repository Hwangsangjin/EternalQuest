// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EQItemBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEQItemBase::AEQItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(MeshComp);
	ItemVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ItemVFX Component"));
	ItemVFX->SetupAttachment(MeshComp);
	ItemVFX->SetUsingAbsoluteRotation(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Ref(
		TEXT("/Game/Assets/Cute_Little_Animals/Tree_And_Box/Mesh/SM_Box.SM_Box"));
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

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> CommonVFXRef(TEXT(
		"/Script/Niagara.NiagaraSystem'/Game/Assets/VFX_Pickup_Pack_1/VFX/Presets/NE_VFX_Item_Common_Loop_01.NE_VFX_Item_Common_Loop_01'"));
	if (CommonVFXRef.Succeeded())
	{
		CommonVFX = CommonVFXRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> UnCommonVFXRef(TEXT(
		"/Script/Niagara.NiagaraSystem'/Game/Assets/VFX_Pickup_Pack_1/VFX/Presets/NE_VFX_Item_Uncommon_Loop_01.NE_VFX_Item_Uncommon_Loop_01'"));
	if (UnCommonVFXRef.Succeeded())
	{
		UnCommonVFX = UnCommonVFXRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EpicVFXRef(TEXT(
		"/Script/Niagara.NiagaraSystem'/Game/Assets/VFX_Pickup_Pack_1/VFX/Presets/NE_VFX_Item_Epic_Loop_01.NE_VFX_Item_Epic_Loop_01'"));
	if (EpicVFXRef.Succeeded())
	{
		EpicVFX = EpicVFXRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> LegendaryVFXRef(TEXT(
		"/Script/Niagara.NiagaraSystem'/Game/Assets/VFX_Pickup_Pack_1/VFX/Presets/NE_VFX_Item_Legendary_Loop_01.NE_VFX_Item_Legendary_Loop_01'"));
	if (LegendaryVFXRef.Succeeded())
	{
		LegendaryVFX = LegendaryVFXRef.Object;
	}

	MeshComp->SetSimulatePhysics(true);
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
	//
	auto FindItem = ItemName.DataTable->FindRow<FEQItem>(ItemName.RowName, "");
	if (FindItem)
	{
		if (FindItem->Grade == 0)
		{
			ItemVFX->SetAsset(CommonVFX);
		}
		else if (FindItem->Grade == 1)
		{
			ItemVFX->SetAsset(UnCommonVFX);
		}
		else if (FindItem->Grade == 2)
		{
			ItemVFX->SetAsset(EpicVFX);
		}
		else if (FindItem->Grade == 3)
		{
			ItemVFX->SetAsset(LegendaryVFX);
		}
	}
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
