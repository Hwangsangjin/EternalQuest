

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterEnemy.h"
#include "EQBossEnemy.generated.h"
class UEQBossMonsterHPUI;
class UWidgetComponent;
class UEQMonsterAbility;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQBossEnemy : public AEQCharacterEnemy
{
	GENERATED_BODY()
public:
	AEQBossEnemy();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEQBossMonsterHPUI> HPUIFactory;
	UPROPERTY()
	UEQBossMonsterHPUI* BossHp;

	UPROPERTY(EditAnywhere,Category="Ability")
	float DetectRange = 2000.f;
	bool bCanShowHP = false;
	
	virtual void Tick(float DeltaSeconds) override;
	virtual bool GetIsMonsterHit();
	virtual bool GetIsMonsterDie();
	
	virtual void ShowBossHPBar();
	virtual void RemoveBossHPBar();
};
