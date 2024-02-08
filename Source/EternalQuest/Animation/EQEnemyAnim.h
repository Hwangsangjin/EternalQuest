

#pragma once

#include "CoreMinimal.h"
#include "Animation/EQAnimInstance.h"
#include "EQEnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQEnemyAnim : public UEQAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= EnemyFSM)
	EMonsterState State;
	
	//// Spider ////
	UFUNCTION()
	void AnimNotify_ShootWeb();

	//// Scorpion ////
	UFUNCTION()
	void AnimNotify_ScorSkill();
};
