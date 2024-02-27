// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/EQScorpionSkill.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQSpider.h"

AEQScorpionSkill::AEQScorpionSkill()
{
	Speed = 300;
}

void AEQScorpionSkill::FindTarget()
{
	Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AEQScorpionSkill::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle,this,&AEQScorpionSkill::FindTarget,0.1f,true);
}

void AEQScorpionSkill::Tick(float DeltaSeconds)
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

void AEQScorpionSkill::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Self)
	{
		Self->MonsterProjectileHit(OtherActor);
		Destroy();	
	}
}



