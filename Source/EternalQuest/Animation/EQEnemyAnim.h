

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


	UFUNCTION()
	void AnimNotify_ShootWeb();
};
