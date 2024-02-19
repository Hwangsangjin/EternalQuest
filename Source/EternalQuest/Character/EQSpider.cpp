// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQSpider.h"

#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
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

	
}

void AEQSpider::MonsterProjectileHit(AActor* OtherActor)
{
	Super::MonsterProjectileHit(OtherActor);
	AEQSpiderWeb* SpiderWeb = Cast<AEQSpiderWeb>(GetMesh());
	FDamageEvent DamageEvent;
	auto Player = Cast<AEQCharacterPlayer>(OtherActor);
	if(OtherActor == Player)
	{
		OtherActor -> TakeDamage(Ability->ScorpionAttackDamage,DamageEvent,nullptr,SpiderWeb);
	}
}






