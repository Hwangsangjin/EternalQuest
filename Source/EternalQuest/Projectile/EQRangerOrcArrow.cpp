// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/EQRangerOrcArrow.h"

#include "Character/EQNormalEnemy.h"

AEQRangerOrcArrow::AEQRangerOrcArrow()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/ma17_OrcSet/ma032_OrcArcher/Mesh/SM_ma032_Arrow.SM_ma032_Arrow'"));
	if(TempMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(TempMesh.Object);
		MeshComp->SetRelativeRotation(FRotator(0,180,0));
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	Speed = 600;
}

void AEQRangerOrcArrow::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Self)
	{
		Self->MonsterProjectileHit(OtherActor);
		Destroy();	
	}
}
