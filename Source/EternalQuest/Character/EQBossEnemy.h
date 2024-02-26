

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "EQBossEnemy.generated.h"
class UEQBossMonsterHPUI;
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
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	// UEQMonsterAbility* Ability;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	UWidgetComponent* HPComp;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEQBossMonsterHPUI> HPUIFactory;
	UPROPERTY()
	UEQBossMonsterHPUI* BossHp;

	UPROPERTY(EditAnywhere,Category="Ability")
	float DetectRange = 2000.f;
	bool bCanShowHP = false;
	
	virtual void Tick(float DeltaSeconds) override;
	virtual bool GetIsMonsterHit();
	
	virtual void ShowBossHPBar();
	virtual void RemoveBossHPBar();
};
