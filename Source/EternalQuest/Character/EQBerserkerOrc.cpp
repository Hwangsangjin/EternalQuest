// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQBerserkerOrc.h"

#include "EQCharacterPlayer.h"
#include "AI/EQMonsterAbility.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Item/EQItemBase.h"
#include "Kismet/KismetSystemLibrary.h"




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
	WeaponComp_R -> SetupAttachment(GetMesh(),FName("weapon_root_R"));
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
	StartPos_L = CreateDefaultSubobject<USceneComponent>(TEXT("StartPos_L"));
	StartPos_L ->SetupAttachment(WeaponComp_L,FName(TEXT("Axe_StartPos")));
	EndPos_L = CreateDefaultSubobject<USceneComponent>(TEXT("EndPos_L"));
	EndPos_L ->SetupAttachment(WeaponComp_L,FName(TEXT("Axe_EndPos")));
	StartPos_R = CreateDefaultSubobject<USceneComponent>(TEXT("StartPos_R"));
	StartPos_R ->SetupAttachment(WeaponComp_R,FName(TEXT("Axe_StartPos")));
	EndPos_R = CreateDefaultSubobject<USceneComponent>(TEXT("EndPos_R"));
	EndPos_R ->SetupAttachment(WeaponComp_R,FName(TEXT("Axe_EndPos")));
	
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
	ShoulderMesh -> SetupAttachment(GetMesh(),FName("Chest"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>ShoTemp(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/ma17_OrcSet/ma035_OrcBerserker/Mesh/SK_ma035_Pauldrons.SK_ma035_Pauldrons'"));
	if(ShoTemp.Succeeded())
	{
		ShoulderMesh->SetSkeletalMesh(ShoTemp.Object);
		ShoulderMesh->SetRelativeLocation(FVector(-60,0,0));
		//(Pitch=-90.000000,Yaw=180.000000,Roll=180.000000)
		ShoulderMesh->SetRelativeRotation(FRotator(-90,180,180));
	}

	Experience = 500;
}

UBehaviorTree* AEQBerserkerOrc::GetBehaviorTree()
{
	return Tree;
}


void AEQBerserkerOrc::CheckAttack_L(float Damage, float Radius)
{
	TArray<FHitResult> OutHitArray;
	if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartPos_L->GetComponentLocation(), EndPos_L->GetComponentLocation(), Radius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, {}, 
			EDrawDebugTrace::None, OutHitArray, true))
	{
		for (FHitResult Iter : OutHitArray)
		{
			if (auto Player = Cast<AEQCharacterPlayer>(Iter.GetActor()))
			{
				if (!DamagedPlayers.Contains(Player))
				{
					FDamageEvent DamageEvent;
					Player->TakeDamage(Damage, DamageEvent, nullptr, this);
					DamagedPlayers.Add(Player);
				}
			}
		}
	}
}

void AEQBerserkerOrc::CheckAttack_R(float Damage, float Radius)
{
	TArray<FHitResult> OutHitArray;
	if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartPos_R->GetComponentLocation(), EndPos_R->GetComponentLocation(), Radius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, {}, 
			EDrawDebugTrace::None, OutHitArray, true))
	{
		for (FHitResult Iter : OutHitArray)
		{
			if (auto Player = Cast<AEQCharacterPlayer>(Iter.GetActor()))
			{
				if (!DamagedPlayers.Contains(Player))
				{
					FDamageEvent DamageEvent;
					Player->TakeDamage(Damage, DamageEvent, nullptr, this);
					DamagedPlayers.Add(Player);
				}
			}
		}
	}
	
}

void AEQBerserkerOrc::EndAttack()
{
	DamagedPlayers.Empty();
}

void AEQBerserkerOrc::DropItem()
{
	Super::DropItem();
	auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
	if (CurrItem)
	{
		CurrItem->ItemName.DataTable = ItemDataTable;
		CurrItem->ItemName.RowName = TEXT("OrcTooth");
		CurrItem->ItemType = EEQItemType::Questitem;
		CurrItem->ItemQuantity = 2;
	}
	CurrItem->FinishSpawning(GetActorTransform());
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
	UE_LOG(LogTemp,Warning,TEXT("DodgeAnimation!!!!!!!!!!!!!!!!"));
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


