// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQArcherOrc.h"

#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Item/EQItemBase.h"
#include "Projectile/EQRangerOrcArrow.h"

AEQArcherOrc::AEQArcherOrc()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma032_OrcArcher/Mesh/SK_ma032_OrcArcher.SK_ma032_OrcArcher'"));
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
	ConstructorHelpers::FObjectFinder<USkeletalMesh> HelmetTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma032_OrcArcher/Mesh/SK_ma032_Helmet.SK_ma032_Helmet'"));
	if(HelmetTemp.Succeeded())
	{
		HelmetComp->SetSkeletalMesh(HelmetTemp.Object);
		HelmetComp->SetRelativeLocation(FVector(-106,0,0));
		HelmetComp->SetRelativeRotation(FRotator(90,-258,-78));
		HelmetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	QuiverComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PauldronsComp"));
	QuiverComp -> SetupAttachment(GetMesh(),FName("Back"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> ClavTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma032_OrcArcher/Mesh/SK_ma032_Quiver.SK_ma032_Quiver'"));
	if(ClavTemp.Succeeded())
	{
		QuiverComp->SetSkeletalMesh(ClavTemp.Object);
		QuiverComp->SetRelativeLocation(FVector(-47.f,-7.f,-9.f));
		QuiverComp->SetRelativeRotation(FRotator(48.f,101.f,-74.f));
		QuiverComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	WeaponComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp"));
	WeaponComp -> SetupAttachment(GetMesh(),FName("WeaponSocket"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempWeapon(TEXT("/Script/Engine.StaticMesh'/Game/Assets/ma17_OrcSet/ma032_OrcArcher/Mesh/SM_ma032_Weapon.SM_ma032_Weapon'"));
	if(TempWeapon.Succeeded())
	{
		WeaponComp->SetStaticMesh(TempWeapon.Object);
		WeaponComp->SetRelativeRotation(FRotator(0,180,0));
		WeaponComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	Experience = 40;
}

FString AEQArcherOrc::SetName()
{
	Super::SetName();
	MonsterName = TEXT("숟가락");
	return MonsterName;
}

void AEQArcherOrc::MonsterProjectileHit(AActor* OtherActor)
{
	Super::MonsterProjectileHit(OtherActor);
	AEQRangerOrcArrow* OrcArrow = Cast<AEQRangerOrcArrow>(GetMesh());
	FDamageEvent DamageEvent;
	auto Player = Cast<AEQCharacterPlayer>(OtherActor);
	if(OtherActor == Player)
	{
		Player -> TakeDamage(Ability->OrcArrowDamage,DamageEvent,nullptr,OrcArrow);
	}
}

void AEQArcherOrc::DropItem()
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
			CurrItem4->ItemName.RowName = TEXT("SeSacSoulShield");
			CurrItem4->ItemType = EEQItemType::Equipment;
			CurrItem4->ItemQuantity = 1;
		}
		CurrItem4->FinishSpawning(GetActorTransform());
	}
	
}

int32 AEQArcherOrc::GetExperience()
{
	return Experience;
}
