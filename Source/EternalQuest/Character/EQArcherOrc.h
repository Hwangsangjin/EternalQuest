// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQNormalEnemy.h"
#include "EQArcherOrc.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQArcherOrc : public AEQNormalEnemy
{
	GENERATED_BODY()
	AEQArcherOrc();
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* HelmetComp;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* QuiverComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponComp;

	virtual FString SetName() override;
	virtual void MonsterProjectileHit(AActor* OtherActor);
	virtual void DropItem() override;
	virtual int32 GetExperience() override;

};
