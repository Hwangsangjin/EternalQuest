// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "EQCharacterEnemy.generated.h"

class UWidgetComponent;
class UEQDamageAmoutUI;
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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
    
public:
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
    UPROPERTY()
    UDamageType* Type;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEQDamageAmoutUI> DamageFactory;
	UPROPERTY(EditAnywhere)
	UWidgetComponent* DamageComp;
};
