


#include "Character/EQCharacterNonPlayer.h"

#include "AI/EQMonsterAbility.h"


AEQCharacterNonPlayer::AEQCharacterNonPlayer()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DTItemRef(TEXT("/Game/Blueprints/Data/DT_Item.DT_Item"));
	if (DTItemRef.Succeeded())
	{
		EQSlot.ItemID.DataTable = DTItemRef.Object;
	}
	
}

