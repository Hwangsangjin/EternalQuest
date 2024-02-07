


#include "Animation/EQEnemyAnim.h"

#include "AI/EQBaseFSM.h"
#include "Character/EQSpider.h"

void UEQEnemyAnim::AnimNotify_ShootWeb()
{
	AEQSpider* Spider = Cast<AEQSpider>(TryGetPawnOwner());
	if(Spider != nullptr)
	{
		Spider->BaseFsm->ShootWeb();
	}
}
