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
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	UBehaviorTree* Tree;
	
	UBehaviorTree* GetBehaviorTree();
};
