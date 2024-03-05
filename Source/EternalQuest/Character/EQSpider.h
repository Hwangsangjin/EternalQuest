// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQNormalEnemy.h"
#include "EQSpider.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQSpider : public AEQNormalEnemy
{
	GENERATED_BODY()

	AEQSpider();

public:
	virtual void MonsterProjectileHit(AActor* OtherActor) override;
	virtual FString SetName() override;
	virtual void DropItem() override;
	virtual int32 GetExperience() override;

};
