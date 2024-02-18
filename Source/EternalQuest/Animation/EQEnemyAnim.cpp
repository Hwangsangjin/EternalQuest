


#include "Animation/EQEnemyAnim.h"

#include "AI/EQBaseFSM.h"
#include "Character/EQScorpion.h"
#include "Character/EQSpider.h"
#include "Net/UnrealNetwork.h"



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

void UEQEnemyAnim::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UEQEnemyAnim, State);
	
}