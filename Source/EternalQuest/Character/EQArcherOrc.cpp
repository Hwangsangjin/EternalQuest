// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQArcherOrc.h"

#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
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