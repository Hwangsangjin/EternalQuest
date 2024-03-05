// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQSpider.h"

#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Item/EQItemBase.h"
#include "Projectile/EQSpiderWeb.h"

AEQSpider::AEQSpider()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/CasualFantasyMonster/Meshes/Spider/SK_Spider.SK_Spider'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeScale3D(FVector(0.3f));
		GetMesh()->SetRelativeLocation(FVector(10,0,-60));
		GetCapsuleComponent()->SetCapsuleHalfHeight(74.f);
		GetCapsuleComponent()->SetCapsuleRadius(70);
	}

	Experience = 40;
}

void AEQSpider::MonsterProjectileHit(AActor* OtherActor)
{
	Super::MonsterProjectileHit(OtherActor);
	AEQSpiderWeb* SpiderWeb = Cast<AEQSpiderWeb>(GetMesh());
	FDamageEvent DamageEvent;
	auto Player = Cast<AEQCharacterPlayer>(OtherActor);
	if(OtherActor == Player)
	{
		Player -> TakeDamage(Ability->ScorpionAttackDamage,DamageEvent,nullptr,SpiderWeb);
	}
}

FString AEQSpider::SetName()
{
	Super::SetName();
	MonsterName = TEXT("스파이더");
	return MonsterName;
}

void AEQSpider::DropItem()
{
	float RandomValue = FMath::FRand();
	if(RandomValue <= 0.6f)
	{
		auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
		if (CurrItem)
		{
			CurrItem->ItemName.DataTable = ItemDataTable;
			CurrItem->ItemName.RowName = TEXT("ManaPostion");
			CurrItem->ItemType = EEQItemType::Consumtion;
			CurrItem->ItemQuantity = 1;
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
			CurrItem->ItemQuantity = 1;
		}
		CurrItem->FinishSpawning(GetActorTransform());
	}
}

int32 AEQSpider::GetExperience()
{
	return Experience;
}






