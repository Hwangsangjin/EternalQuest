// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQWarriorOrc.h"

#include "Components/CapsuleComponent.h"
#include "Item/EQItemBase.h"

AEQWarriorOrc::AEQWarriorOrc()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma030_OrcWarrior/Mesh/SK_ma030_Helmet.SK_ma030_Helmet'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0,0,-90));
		//(Pitch=0.000000,Yaw=-90.000000,Roll=0.000000)
		GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
		GetMesh()->SetRelativeScale3D(FVector(1.5f));
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCapsuleRadius(45.f);
		GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	}
	HelmetComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HelmetComp"));
	HelmetComp -> SetupAttachment(GetMesh(),FName("Helmet"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> HelmetTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma030_OrcWarrior/Mesh/SK_ma030_OrcWarrior.SK_ma030_OrcWarrior'"));
	if(HelmetTemp.Succeeded())
	{
		HelmetComp->SetSkeletalMesh(HelmetTemp.Object);
		HelmetComp->SetRelativeLocation(FVector(-85,0,0));
		HelmetComp->SetRelativeRotation(FRotator(90,720,540));
		HelmetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	PauldronsComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PauldronsComp"));
	PauldronsComp -> SetupAttachment(GetMesh(),FName("Clav"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> ClavTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma030_OrcWarrior/Mesh/SK_ma030_Pauldrons.SK_ma030_Pauldrons'"));
	if(ClavTemp.Succeeded())
	{
		PauldronsComp->SetSkeletalMesh(ClavTemp.Object);
		PauldronsComp->SetRelativeLocation(FVector(33.f,2.f,48.f));
		PauldronsComp->SetRelativeRotation(FRotator(48.f,168.f,164.f));
		PauldronsComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	WeaponComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp"));
	WeaponComp -> SetupAttachment(GetMesh(),FName("WeaponSocket"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempWeapon(TEXT("/Script/Engine.StaticMesh'/Game/Assets/ma17_OrcSet/ma030_OrcWarrior/Mesh/SK_ma030_Weapon.SK_ma030_Weapon'"));
	if(TempWeapon.Succeeded())
	{
		WeaponComp->SetStaticMesh(TempWeapon.Object);
		//(Pitch=-0.000000,Yaw=180.000000,Roll=0.000000)
		WeaponComp->SetRelativeRotation(FRotator(0,180,0));
		WeaponComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	bReplicates = true;
	SetReplicateMovement(true);
	Experience = 30;
}

void AEQWarriorOrc::DropItem()
{
	Super::DropItem();
	float RandomValue = FMath::FRand();
	if(RandomValue <= 0.6f)
	{
		auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
		if (CurrItem)
		{
			CurrItem->ItemName.DataTable = ItemDataTable;
			CurrItem->ItemName.RowName = TEXT("ManaPostion");
			CurrItem->ItemType = EEQItemType::Consumtion;
			CurrItem->ItemQuantity = 2;
		}
		CurrItem->FinishSpawning(GetActorTransform());	
	}
	else
	{
		auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
		if (CurrItem)
		{
			CurrItem->ItemName.DataTable = ItemDataTable;
			CurrItem->ItemName.RowName = TEXT("HealthPostion");
			CurrItem->ItemType = EEQItemType::Consumtion;
			CurrItem->ItemQuantity = 2;
		}
		CurrItem->FinishSpawning(GetActorTransform());
	}

	auto CurrItem3 = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
	if (CurrItem3)
	{
		CurrItem3->ItemName.DataTable = ItemDataTable;
		CurrItem3->ItemName.RowName = TEXT("SeSacSoul");
		CurrItem3->ItemType = EEQItemType::Material;
		CurrItem3->ItemQuantity = 1;
	}
	CurrItem3->FinishSpawning(GetActorTransform());
}

FString AEQWarriorOrc::SetName()
{
	Super::SetName();
	MonsterName = TEXT("망나니");
	return MonsterName;
}

