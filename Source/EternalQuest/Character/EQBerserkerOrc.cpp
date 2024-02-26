// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQBerserkerOrc.h"

#include "AI/EQMonsterAbility.h"
#include "Components/CapsuleComponent.h"


AEQBerserkerOrc::AEQBerserkerOrc()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma035_OrcBerserker/Mesh/SK_ma035_OrcBerserker.SK_ma035_OrcBerserker'"));
	if(TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeScale3D(FVector(3.5f));
		GetMesh()->SetRelativeLocation(FVector(0,0,-200));
		GetCapsuleComponent()->SetCapsuleHalfHeight(200.f);
		GetCapsuleComponent()->SetCapsuleRadius(100.f);
	}
	WeaponComp_L = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp_L"));
	WeaponComp_L -> SetupAttachment(GetMesh(),FName("weapon_root_L"));
	WeaponComp_R = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComp_R"));
	WeaponComp_R ->SetupAttachment(GetMesh(),FName("weapon_root_R"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/ma17_OrcSet/ma035_OrcBerserker/Mesh/SM_ma035_Weapon.SM_ma035_Weapon'"));
	if(WeaponMesh.Succeeded())
	{
		WeaponComp_L->SetStaticMesh(WeaponMesh.Object);
		WeaponComp_L->SetRelativeRotation(FRotator(0,0,-90));
		WeaponComp_L->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponComp_R->SetStaticMesh(WeaponMesh.Object);
		WeaponComp_R->SetRelativeRotation(FRotator(0,0,-90));
		WeaponComp_R->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	HelmetMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HelmetMesh"));
	HelmetMesh -> SetupAttachment(GetMesh(),FName("Halmet"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>HatTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma035_OrcBerserker/Mesh/SK_ma035_Helmet.SK_ma035_Helmet'"));
	if(HatTemp.Succeeded())
	{
		HelmetMesh->SetSkeletalMesh(HatTemp.Object);
		HelmetMesh->SetRelativeLocation(FVector(-85,0,0));
		// (Pitch=90.000000,Yaw=1350.000000,Roll=-995.000000)
		HelmetMesh->SetRelativeRotation(FRotator(90,1350,-995));
	}
	ShoulderMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderMesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>ShoTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma035_OrcBerserker/Mesh/SK_ma035_Pauldrons.SK_ma035_Pauldrons'"));
	if(ShoTemp.Succeeded())
	{
		ShoulderMesh->SetSkeletalMesh(ShoTemp.Object);
		ShoulderMesh->SetRelativeLocation(FVector(-60,0,0));
		//(Pitch=-90.000000,Yaw=180.000000,Roll=180.000000)
		ShoulderMesh->SetRelativeRotation(FRotator(-90,180,180));
	}
}

UBehaviorTree* AEQBerserkerOrc::GetBehaviorTree()
{
	return Tree;
}

void AEQBerserkerOrc::MultiRPC_Die_Implementation()
{
	PlayAnimMontage(Montage,1,FName("Die"));
}

void AEQBerserkerOrc::MultiRPC_Combo_Implementation()
{
	PlayAnimMontage(Montage,1,FName("Combo"));
}

void AEQBerserkerOrc::MultiRPC_Dodge_Implementation()
{
	PlayAnimMontage(Montage,1,FName("Dodge"));
}

void AEQBerserkerOrc::MultiRPC_Smash_Implementation()
{
	PlayAnimMontage(Montage,1,FName("Smash"));
}

void AEQBerserkerOrc::MultiRPC_Attack_Implementation()
{
	PlayAnimMontage(Montage,1,FName("Attack1"));
}


