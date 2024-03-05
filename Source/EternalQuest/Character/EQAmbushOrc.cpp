// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQAmbushOrc.h"

#include "Components/CapsuleComponent.h"
#include "Item/EQItemBase.h"

AEQAmbushOrc::AEQAmbushOrc()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma033_OrcFighter/Mesh/SK_ma033_OrcFighter.SK_ma033_OrcFighter'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0,0,-90));
		//(Pitch=0.000000,Yaw=-90.000000,Roll=0.000000)
		GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
		//GetMesh()->SetRelativeScale3D(FVector(1.5f));
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCapsuleRadius(45.f);
		GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	}
	HelmetComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HelmetComp"));
	HelmetComp -> SetupAttachment(GetMesh(),FName("Helmet"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> HelmetTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma033_OrcFighter/Mesh/SK_ma033_Helmet.SK_ma033_Helmet'"));
	if(HelmetTemp.Succeeded())
	{
		HelmetComp->SetSkeletalMesh(HelmetTemp.Object);
		//(X=-80.000005,Y=-0.000000,Z=0.000000)
		HelmetComp->SetRelativeLocation(FVector(-85,0,0));
		//(Pitch=90.000000,Yaw=-90.186615,Roll=90.000000)
		HelmetComp->SetRelativeRotation(FRotator(90,-90,90));
		HelmetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	PauldronsComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PauldronsComp"));
	PauldronsComp -> SetupAttachment(GetMesh(),FName("Chest"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> ClavTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma033_OrcFighter/Mesh/SK_ma033_Pauldrons.SK_ma033_Pauldrons'"));
	if(ClavTemp.Succeeded())
	{
		PauldronsComp->SetSkeletalMesh(ClavTemp.Object);
		//(X=-60.000000,Y=0.000000,Z=0.000000)
		PauldronsComp->SetRelativeLocation(FVector(-60.f,12.f,0.f));
		//(Pitch=90.000000,Yaw=-250.000000,Roll=295.000000)
		PauldronsComp->SetRelativeRotation(FRotator(90.f,-250.f,295.f));
		PauldronsComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	WeaponComp_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp_L"));
	WeaponComp_L -> SetupAttachment(GetMesh(),FName("Weapon_L"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempWeapon(TEXT("/Script/Engine.StaticMesh'/Game/Assets/ma17_OrcSet/ma033_OrcFighter/Mesh/SM_ma033_Weapon_2.SM_ma033_Weapon_2'"));
	if(TempWeapon.Succeeded())
	{
		WeaponComp_L->SetStaticMesh(TempWeapon.Object);
		//(Pitch=9.999999,Yaw=-180.000000,Roll=180.000000)
		WeaponComp_L->SetRelativeRotation(FRotator(10,-180,180));
		WeaponComp_L->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	WeaponComp_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon_R"));
	WeaponComp_R -> SetupAttachment(GetMesh(),FName("Weapon_R"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempWeaponR(TEXT("/Script/Engine.StaticMesh'/Game/Assets/ma17_OrcSet/ma033_OrcFighter/Mesh/SM_ma033_Weapon_1.SM_ma033_Weapon_1'"));
	if(TempWeaponR.Succeeded())
	{
		WeaponComp_R->SetStaticMesh(TempWeaponR.Object);
		//(X=0.000000,Y=6.666649,Z=6.666685)
		WeaponComp_R->SetRelativeLocation(FVector(0.f,6.6f,3.5f));
		//(Pitch=0.000000,Yaw=179.999999,Roll=0.000153)
		WeaponComp_R->SetRelativeRotation(FRotator(0,180,0));
		WeaponComp_R->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	Experience = 35;
}

void AEQAmbushOrc::BeginPlay()
{
	Super::BeginPlay();
	MultiPRC_Ambushing();
}

FString AEQAmbushOrc::SetName()
{
	Super::SetName();
	MonsterName = TEXT("백정");
	return MonsterName;
}

void AEQAmbushOrc::DropItem()
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

	if(RandomValue <= 0.4)
	{
		auto CurrItem4 = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
		if (CurrItem4)
		{
			CurrItem4->ItemName.DataTable = ItemDataTable;
			CurrItem4->ItemName.RowName = TEXT("Dan_Sword");
			CurrItem4->ItemType = EEQItemType::Equipment;
			CurrItem4->ItemQuantity = 2;
		}
		CurrItem4->FinishSpawning(GetActorTransform());
	}
	
}

int32 AEQAmbushOrc::GetExperience()
{
	return Experience;
}

void AEQAmbushOrc::MultiPRC_Ambushing_Implementation()
{
	PlayAnimMontage(Montage,1,FName("Ambush"));
}


