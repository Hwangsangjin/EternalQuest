// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EQMeleeFSM.h"
#include "AI/EQBaseFSM.h"
#include "EQScorpionFSM.generated.h"


class AEQScorpionSkill;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQScorpionFSM : public UEQBaseFSM
{
	GENERATED_BODY()
	

	virtual void BeginPlay() override;

protected:
	virtual void TickMove() override;
	virtual void TickAttack() override;
	virtual void TickHit() override;
	virtual void TickDie() override;

public:
	UPROPERTY(EditAnywhere,Category="MonsterAnim")
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere,Category="Skills")
	TSubclassOf<AEQScorpionSkill> SkillFactory;

	
	
private:
	float MeleeAttackRange = 500;
	float RangeAttackRange = 1500;

public:
	void ScorpionAttack();
	void ScorpionSkill();
	void CheckPlayerLoc();
	void SetFocus();

	virtual void ScorpionPrj() override;

	
};
