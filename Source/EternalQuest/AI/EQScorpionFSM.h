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
	virtual void TickDie() override;
	virtual void MeleeAttackCheck() override;

public:
	UPROPERTY(EditAnywhere,Category="Skills")
	TSubclassOf<AEQScorpionSkill> SkillFactory;

	
	
private:
	float MeleeAttackRange = 400;
	float MinRangeAttackRange = 800;
	float MaxRangeAttackRange = 1500;
	bool bIsUsingSkill;


public:
	void ScorpionAttack();
	void ScorpionSkill();
	void CheckPlayerLoc();
	void SetFocus();

	virtual void ScorpionPrj() override;

	UFUNCTION(Server,Reliable)
	void ServerRPC_ScorpionAttack();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_ScorpionAttack();

	UFUNCTION(Server,Reliable)
	void ServerRPC_ScorpionDie();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_ScopionDie();
};
