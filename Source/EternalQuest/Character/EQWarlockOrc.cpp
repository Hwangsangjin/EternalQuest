// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQWarlockOrc.h"

#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Projectile/EQWarlockOrcSkill.h"

AEQWarlockOrc::AEQWarlockOrc()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma034_OrcWarlock/Mesh/SK_ma034_OrcWarlock.SK_ma034_OrcWarlock'"));
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
	ConstructorHelpers::FObjectFinder<USkeletalMesh> HelmetTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma034_OrcWarlock/Mesh/SK_ma034_Helmet.SK_ma034_Helmet'"));
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
	ConstructorHelpers::FObjectFinder<USkeletalMesh> ClavTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma034_OrcWarlock/Mesh/SK_ma034_Pauldrons.SK_ma034_Pauldrons'"));
	if(ClavTemp.Succeeded())
	{
		PauldronsComp->SetSkeletalMesh(ClavTemp.Object);
		//(X=-60.000000,Y=0.000000,Z=0.000000)
		PauldronsComp->SetRelativeLocation(FVector(-60.f,0,0.f));
		//(Pitch=90.000000,Yaw=-250.000000,Roll=295.000000)
		PauldronsComp->SetRelativeRotation(FRotator(90.f,-250.f,295.f));
		PauldronsComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	WeaponComp_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp_L"));
	WeaponComp_L -> SetupAttachment(GetMesh(),FName("Weapon_L"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempWeapon(TEXT("/Script/Engine.StaticMesh'/Game/Assets/ma17_OrcSet/ma034_OrcWarlock/Mesh/SM_ma034_Weapon_2.SM_ma034_Weapon_2'"));
	if(TempWeapon.Succeeded())
	{
		WeaponComp_L->SetStaticMesh(TempWeapon.Object);
		//(Pitch=9.999999,Yaw=-180.000000,Roll=180.000000)
		WeaponComp_L->SetRelativeRotation(FRotator(10,-180,180));
		WeaponComp_L->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	WeaponComp_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon_R"));
	WeaponComp_R -> SetupAttachment(GetMesh(),FName("Weapon_R"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempWeaponR(TEXT("/Script/Engine.StaticMesh'/Game/Assets/ma17_OrcSet/ma034_OrcWarlock/Mesh/SM_ma034_Weapon_1.SM_ma034_Weapon_1'"));
	if(TempWeaponR.Succeeded())
	{
		WeaponComp_R->SetStaticMesh(TempWeaponR.Object);
		//(X=0.000000,Y=6.666649,Z=6.666685)
		WeaponComp_R->SetRelativeLocation(FVector(0.f,6.6f,6.6f));
		//(Pitch=0.000000,Yaw=179.999999,Roll=0.000153)
		WeaponComp_R->SetRelativeRotation(FRotator(0,180,0));
		WeaponComp_R->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
}

void AEQWarlockOrc::MonsterProjectileHit(AActor* OtherActor)
{
	Super::MonsterProjectileHit(OtherActor);
	
	AEQWarlockOrcSkill* WarlockOrcSkill = Cast<AEQWarlockOrcSkill>(GetMesh());
	FDamageEvent DamageEvent;
	auto Player = Cast<AEQCharacterPlayer>(OtherActor);
	if(OtherActor == Player)
	{
		Player -> TakeDamage(Ability->OrcSkillDamage,DamageEvent,nullptr,WarlockOrcSkill);
	}
}

FString AEQWarlockOrc::SetName()
{
	Super::SetName();
	MonsterName = TEXT("Faker");
	return MonsterName;
}
