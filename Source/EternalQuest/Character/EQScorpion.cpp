


#include "Character/EQScorpion.h"
#include "Projectile/EQScorpionSkill.h"
#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "AI/EQScorpionFSM.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Item/EQItemBase.h"

AEQScorpion::AEQScorpion()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/CasualFantasyMonster/Meshes/Scorpion/SK_Scorpion.SK_Scorpion'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeScale3D(FVector(2.5f));
		GetCapsuleComponent()->SetCapsuleHalfHeight(120.f);
		GetCapsuleComponent()->SetCapsuleRadius(100.f);
	}
}

void AEQScorpion::MonsterProjectileHit(AActor* OtherActor)
{
	Super::MonsterProjectileHit(OtherActor);
	AEQScorpionSkill* Skill = Cast<AEQScorpionSkill>(GetMesh());
	FDamageEvent DamageEvent;
	auto Player = Cast<AEQCharacterPlayer>(OtherActor);
	if(OtherActor == Player)
	{
		Player -> TakeDamage(Ability->SpiderWebDamage,DamageEvent,nullptr,Skill);
	}
}

FString AEQScorpion::SetName()
{
	Super::SetName();
	MonsterName = TEXT("스콜피");
	return MonsterName;
}

void AEQScorpion::DropItem()
{
	auto CurrItem3 = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
	if (CurrItem3)
	{
		CurrItem3->ItemName.DataTable = ItemDataTable;
		CurrItem3->ItemName.RowName = TEXT("PenguinSword");
		CurrItem3->ItemType = EEQItemType::Questitem;
		CurrItem3->ItemQuantity = 1;
	}
	CurrItem3->FinishSpawning(GetActorTransform());

	auto CurrItem4 = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
	if (CurrItem4)
	{
		CurrItem4->ItemName.DataTable = ItemDataTable;
		CurrItem4->ItemName.RowName = TEXT("HealingPostion");
		CurrItem4->ItemType = EEQItemType::Questitem;
		CurrItem4->ItemQuantity = 2;
	}
	CurrItem4->FinishSpawning(GetActorTransform());
	
	float RandValue = FMath::FRand();
	if(RandValue <= 0.5f)
	{
		auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
		if (CurrItem)
		{
			CurrItem->ItemName.DataTable = ItemDataTable;
			CurrItem->ItemName.RowName = TEXT("HealingPostion");
			CurrItem->ItemType = EEQItemType::Questitem;
			CurrItem->ItemQuantity = 2;
		}
		CurrItem->FinishSpawning(GetActorTransform());
	}
	else
	{
		auto CurrItem2 = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
		if (CurrItem2)
		{
			CurrItem2->ItemName.DataTable = ItemDataTable;
			CurrItem2->ItemName.RowName = TEXT("ManaPostion");
			CurrItem2->ItemType = EEQItemType::Consumtion;
			CurrItem2->ItemQuantity = 2;
		}
		CurrItem2->FinishSpawning(GetActorTransform());
	}
}
