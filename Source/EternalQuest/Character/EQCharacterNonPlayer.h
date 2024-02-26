

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterBase.h"
#include "Struct/EQStructEnumBase.h"
#include "EQCharacterNonPlayer.generated.h"

class UEQMonsterAbility;
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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UEQMonsterAbility* Ability;

protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;
	UPROPERTY()
	UDamageType* Type;
};
