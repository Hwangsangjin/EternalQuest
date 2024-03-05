// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQMush.h"

#include "AI/EQMeleeFSM.h"
#include "Item/EQItemBase.h"

AEQMush::AEQMush()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/CasualFantasyMonster/Meshes/Mushroom/SK_Mushroom.SK_Mushroom'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0,0,-30));
	}
	Experience = 10;
}

FString AEQMush::SetName()
{
	Super::SetName();
	MonsterName = TEXT("버섯커");
	return MonsterName;
}

void AEQMush::DropItem()
{
	float RandValue = FMath::FRand();
	if(RandValue <= 0.5f)
	{
		auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
		if (CurrItem)
		{
			CurrItem->ItemName.DataTable = ItemDataTable;
			CurrItem->ItemName.RowName = TEXT("MushRoomGem");
			CurrItem->ItemType = EEQItemType::Questitem;
			CurrItem->ItemQuantity = 1;
		}
		CurrItem->FinishSpawning(GetActorTransform());
	}
	else
	{
		auto CurrItem2 = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
		if (CurrItem2)
		{
			CurrItem2->ItemName.DataTable = ItemDataTable;
			CurrItem2->ItemName.RowName = TEXT("Apple");
			CurrItem2->ItemType = EEQItemType::Consumtion;
			CurrItem2->ItemQuantity = 1;
		}
		CurrItem2->FinishSpawning(GetActorTransform());
	}
	
	
}



