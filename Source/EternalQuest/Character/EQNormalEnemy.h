

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "EQNormalEnemy.generated.h"


class UWidgetComponent;
class UEQMonsterAbility;
class UEQBaseFSM;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQNormalEnemy : public AEQCharacterNonPlayer
{
	GENERATED_BODY()
public:
	AEQNormalEnemy();

	UPROPERTY(EditAnywhere,Category="FSM")
	UEQBaseFSM* BaseFsm;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	UEQMonsterAbility* Ability;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Ability")
	UWidgetComponent* HPComp;
	
	
	void Tick(float DeltaSeconds) override;
	
};
