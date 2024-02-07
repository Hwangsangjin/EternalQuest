

#pragma once

#include "CoreMinimal.h"
#include "AI/EQBaseFSM.h"
#include "EQMeleeFSM.generated.h"

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
	

	UPROPERTY(EditAnywhere,Category="MonsterAnim")
	UAnimMontage* AnimMontage;
	
	
	
};
