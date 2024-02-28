// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/EQEnemyProjectile.h"
#include "EQRangerOrcArrow.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQRangerOrcArrow : public AEQEnemyProjectile
{
	GENERATED_BODY()
public:
	AEQRangerOrcArrow();
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
