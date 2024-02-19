// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQNormalEnemy.h"
#include "EQScorpion.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQScorpion : public AEQNormalEnemy
{
	GENERATED_BODY()

	AEQScorpion();

	virtual void MonsterProjectileHit(AActor* OtherActor) override;
};
