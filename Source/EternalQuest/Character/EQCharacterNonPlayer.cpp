


#include "Character/EQCharacterNonPlayer.h"

#include "AI/EQMonsterAbility.h"


AEQCharacterNonPlayer::AEQCharacterNonPlayer()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DTItemRef(TEXT("/Game/Blueprints/Data/DT_Item.DT_Item"));
	if (DTItemRef.Succeeded())
	{
		EQSlot.ItemID.DataTable = DTItemRef.Object;
	}
	
	Ability = CreateDefaultSubobject<UEQMonsterAbility>(TEXT("Ability"));
}


float AEQCharacterNonPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Ability->TakeDamage(this,DamageAmount,Type,EventInstigator,DamageCauser);

	return DamageAmount;
}