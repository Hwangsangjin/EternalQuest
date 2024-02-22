

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "EQBossEnemy.generated.h"
class UWidgetComponent;
class UEQMonsterAbility;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQBossEnemy : public AEQCharacterNonPlayer
{
	GENERATED_BODY()
public:
	AEQBossEnemy();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	UEQMonsterAbility* Ability;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	UWidgetComponent* HPComp;

	UPROPERTY(EditAnywhere,Category="Ability")
	float DetectRange = 1500.f;
	bool bCanShowHP = false;

	virtual void Tick(float DeltaSeconds) override;
	virtual bool GetIsMonsterHit();
};
