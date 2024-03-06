

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
	void AnimNotify_SuperAmorEnd();
	UFUNCTION()
	void AnimNotify_DieEnd();

	// Mush //
	UFUNCTION()
	void AnimNotify_MushAttack();

	// Berserker //
	UFUNCTION()
	void AnimNotify_BK_Dodge();
	UFUNCTION()
	void AnimNotify_DamageEnd();

	// ArcherOrc //
	UFUNCTION()
	void AnimNotify_ShootArrow();

	// WarlockOrc //
	UFUNCTION()
	void AnimNotify_WarlockSkill();
	UFUNCTION()
	void AnimNotify_Teleport();

	UFUNCTION()
	void AnimNotify_AbAttack();

	

public:
	// UPROPERTY(Replicated)
	// bool IsDieDone = false;
	
};
