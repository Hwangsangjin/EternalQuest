// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "EQCharacterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQCharacterEnemy : public AEQCharacterNonPlayer
{
	GENERATED_BODY()
public:
		AEQCharacterEnemy();
		UPROPERTY(EditAnywhere,BlueprintReadWrite)
    	UEQMonsterAbility* Ability;
    
    public:
    	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
    	UPROPERTY()
    	UDamageType* Type;
};
