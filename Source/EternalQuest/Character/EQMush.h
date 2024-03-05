// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQNormalEnemy.h"
#include "EQMush.generated.h"

class UEQMeleeFSM;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQMush : public AEQNormalEnemy
{
	GENERATED_BODY()

public:
	AEQMush();
	virtual FString SetName() override;
	virtual void DropItem() override;
	virtual int32 GetExperience() override; 
};
