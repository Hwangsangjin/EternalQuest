// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQNormalEnemy.h"
#include "EQWarlockOrc.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQWarlockOrc : public AEQNormalEnemy
{
	GENERATED_BODY()

public:
	AEQWarlockOrc();
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* HelmetComp;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PauldronsComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponComp_L;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponComp_R;
	

	virtual void MonsterProjectileHit(AActor* OtherActor) override;
	virtual FString SetName() override;
};
