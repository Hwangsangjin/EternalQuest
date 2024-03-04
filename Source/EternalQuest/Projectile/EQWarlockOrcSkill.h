// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/EQEnemyProjectile.h"
#include "EQWarlockOrcSkill.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQWarlockOrcSkill : public AEQEnemyProjectile
{
	GENERATED_BODY()

	AEQWarlockOrcSkill();
	float CurrentTime = 0;
	float FixedTime = 0.3f;
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
