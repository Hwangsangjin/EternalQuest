// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQWarriorOrc.h"

#include "Components/CapsuleComponent.h"

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
}

FString AEQWarriorOrc::SetName()
{
	Super::SetName();
	MonsterName = TEXT("망나니");
	return MonsterName;
}
