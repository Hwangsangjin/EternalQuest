// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQBossEnemy.h"
#include "EQBerserkerOrc.generated.h"

class UEQMonsterAbility;
class UBehaviorTree;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQBerserkerOrc : public AEQBossEnemy
{
	GENERATED_BODY()
	
	
public:
	AEQBerserkerOrc();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	UStaticMeshComponent* WeaponComp_L;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	UStaticMeshComponent* WeaponComp_R;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	UBehaviorTree* Tree;
	
	UBehaviorTree* GetBehaviorTree();

	UPROPERTY(EditAnywhere,Blueprintable,Category="Animaition")
	UAnimMontage*Montage;

	
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_Attack();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_Smash();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_Combo();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_Dodge();
	
};
