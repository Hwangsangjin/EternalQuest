// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/EQWarlockOrcSkill.h"

#include "NiagaraComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQWarlockOrc.h"


AEQWarlockOrcSkill::AEQWarlockOrcSkill()
{
	NiagaraComp->SetRelativeScale3D(FVector(0.3f));
	Speed = 500.f;
}

void AEQWarlockOrcSkill::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(Target)
	{
		FVector Direction = (Target->GetActorLocation()-GetActorLocation()).GetSafeNormal();
		if(CurrentTime > FixedTime)
		{
			FVector LooseTarget = this->GetActorForwardVector();
			Direction = LooseTarget;
			
		}
		SetActorRotation(Direction.Rotation());
		FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaSeconds;
		SetActorLocation(NewLocation);
	}
}

void AEQWarlockOrcSkill::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Self->MonsterProjectileHit(OtherActor);
	this->Destroy();
}
