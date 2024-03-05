// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQNormalEnemy.h"
#include "EQWarriorOrc.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQWarriorOrc : public AEQNormalEnemy
{
	GENERATED_BODY()

	AEQWarriorOrc();

public:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* HelmetComp;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PauldronsComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WeaponComp;

	virtual void DropItem() override;
	virtual FString SetName() override;
	
};
