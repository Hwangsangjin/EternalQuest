

#pragma once

#include "CoreMinimal.h"
#include "AI/EQBaseFSM.h"
#include "EQMeleeFSM.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQMeleeFSM : public UEQBaseFSM
{
	GENERATED_BODY()

private:
	float CurrentTime;
	float AttackTime = 2.0f;
	float AttackRange = 300;
protected:
	virtual void TickAttack() override;
};
