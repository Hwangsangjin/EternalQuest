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
	
}

UBehaviorTree* AEQBerserkerOrc::GetBehaviorTree()
{
	return Tree;
}


