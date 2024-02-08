// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/EQScorpionSkill.h"
#include "Character/EQCharacterPlayer.h"

AEQScorpionSkill::AEQScorpionSkill()
{
	
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
	if(Target)
	{
		FVector Direction = (Target->GetActorLocation()-GetActorLocation()).GetSafeNormal();
		SetActorRotation(Direction.Rotation());
		FVector NewLocation = GetActorLocation() + Direction * Speed * DeltaSeconds;
		SetActorLocation(NewLocation);
	}
}


