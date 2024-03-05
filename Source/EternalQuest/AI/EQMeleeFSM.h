

#pragma once

#include "CoreMinimal.h"
#include "AI/EQBaseFSM.h"
#include "EQMeleeFSM.generated.h"

class UEQMonsterAbility;
class UEQAnimInstance;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQMeleeFSM : public UEQBaseFSM
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void TickAttack() override;
	virtual void TickMove() override;
	virtual void MeleeAttackCheck() override;

	UFUNCTION(Server,Reliable)
	void ServerRPC_MushMove();
	UFUNCTION(Server,Reliable)
	void ServerRPC_MushAttack();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_MushAttack();
	
	
};
