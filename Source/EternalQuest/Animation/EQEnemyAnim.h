

#pragma once

#include "CoreMinimal.h"
#include "Animation/EQAnimInstance.h"
#include "EQEnemyAnim.generated.h"

enum class EMonsterState : uint8;

UCLASS()
class ETERNALQUEST_API UEQEnemyAnim : public UEQAnimInstance
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere,Replicated,BlueprintReadWrite,Category= EnemyFSM)
	EMonsterState State;
	
	//// Spider ////
	UFUNCTION()
	void AnimNotify_ShootWeb();

	//// Scorpion ////
	UFUNCTION()
	void AnimNotify_ScorSkill();
	UFUNCTION()
	void AnimNotify_ScorAttack();
	UFUNCTION()
	void AnimNotify_DieEnd();

	// Mush //
	UFUNCTION()
	void AnimNotify_MushAttack();

	// Berserker //
	 UFUNCTION()
	 void AnimNotify_BK_Dodge();

public:
	bool IsDieDone = false;
	
};
