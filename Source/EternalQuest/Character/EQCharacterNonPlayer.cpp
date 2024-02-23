


#include "Character/EQCharacterNonPlayer.h"


AEQCharacterNonPlayer::AEQCharacterNonPlayer()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DTItemRef(TEXT("/Game/Blueprints/Data/DT_Item.DT_Item"));
	if (DTItemRef.Succeeded())
	{
		EQSlot.ItemID.DataTable = DTItemRef.Object;
	}
}
