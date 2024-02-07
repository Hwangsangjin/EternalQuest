

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterNonPlayer.h"
#include "EQNormalEnemy.generated.h"


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

	

	
};
