// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/EQSpiderWeb.h"
#include "EQScorpionSkill.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQScorpionSkill : public AEQSpiderWeb
{
	GENERATED_BODY()

	AEQScorpionSkill();

	
private:
	FTimerHandle TimerHandle;
	void FindTarget();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	float CurrentTime;
	float FixedTime = 2.0f;
	
	
};
