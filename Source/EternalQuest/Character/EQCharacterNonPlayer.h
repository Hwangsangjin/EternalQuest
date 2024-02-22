

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterBase.h"
#include "Struct/EQStructEnumBase.h"
#include "EQCharacterNonPlayer.generated.h"

struct FEQSlot;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQCharacterNonPlayer : public AEQCharacterBase
{
	GENERATED_BODY()

public:
	AEQCharacterNonPlayer();
	FEQSlot EQSlot;
	
};
