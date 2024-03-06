

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterEnemy.h"
#include "EQNormalEnemy.generated.h"


class UEQNormalMonsterHPBar;
class AEQCharacterPlayer;
class UWidgetComponent;
class UEQMonsterAbility;
class UEQBaseFSM;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQNormalEnemy : public AEQCharacterEnemy
{
	GENERATED_BODY()
public:
	AEQNormalEnemy();
	UPROPERTY(EditAnywhere,Category="FSM")
	UEQBaseFSM* BaseFsm;

	UPROPERTY(EditAnywhere,Category="NPC")
	AEQCharacterNonPlayer* NPC;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	UWidgetComponent* HPComp;

	UPROPERTY(EditAnywhere,Category="Ability")
	float DetectRange = 1500.f;
	bool bCanShowHP = false;
	void ActivateEnemy(const FVector& SpawnLocation);

	
	bool IsActive();

	void Deactivate();

	FString virtual SetName();

	void DieEffect();
	
private:
	UPROPERTY(Replicated)
	bool bIsActive;
public:
	virtual void MonsterProjectileHit(AActor* OtherActor); 
	
protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	FString MonsterName;
};
