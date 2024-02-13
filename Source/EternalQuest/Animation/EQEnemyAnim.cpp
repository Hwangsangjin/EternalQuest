


#include "Animation/EQEnemyAnim.h"

#include "AI/EQBaseFSM.h"
#include "Character/EQScorpion.h"
#include "Character/EQSpider.h"

void UEQEnemyAnim::AnimNotify_ShootWeb()
{
	AEQSpider* Spider = Cast<AEQSpider>(TryGetPawnOwner());
	if(Spider != nullptr)
	{
		Spider->BaseFsm->ShootWeb();
	}
}

void UEQEnemyAnim::AnimNotify_ScorSkill()
{
	AEQScorpion* Scorpion = Cast<AEQScorpion>(TryGetPawnOwner());
	if(Scorpion != nullptr)
	{
		Scorpion->BaseFsm->ScorpionPrj();
	}
}

void UEQEnemyAnim::AnimNotify_DieEnd()
{
	IsDieDone = true;
}
