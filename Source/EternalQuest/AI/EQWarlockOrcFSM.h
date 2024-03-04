// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/EQBaseFSM.h"
#include "EQWarlockOrcFSM.generated.h"

class AEQWarlockTeleportPoint;
class AEQWarlockOrcSkill;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWarlockOrcFSM : public UEQBaseFSM
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere,Category="Skills")
	TSubclassOf<AEQWarlockOrcSkill> SkillFactory;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Skills")
	AEQWarlockTeleportPoint* TPPoint;
	
	
protected:
	virtual void BeginPlay() override;
	virtual void TickMove() override;
	virtual void TickAttack() override;
	virtual void TickDie() override;
	virtual void MeleeAttackCheck() override;

private:
	float MeleeAttackRange = 200;
	float MinRangeAttackRange = 250;
	float MaxRangeAttackRange = 1500;
	bool bIsUsingSkill;


public:
	void WarlockAttack();
	void WarlockSkill();
	virtual void WarlockTeleport() override;
	void CheckPlayerLoc();
	void SetFocus();
	virtual void WarlockPrj() override;


	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_OrcWarlockAttack();
	
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_OrcWarlockSkill();
	
};
