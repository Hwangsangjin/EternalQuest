


#include "Animation/EQEnemyAnim.h"

#include "AI/EQBaseFSM.h"
#include "Character/EQBerserkerOrc.h"
#include "Character/EQMush.h"
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

void UEQEnemyAnim::AnimNotify_ScorAttack()
{
	AEQScorpion* Scorpion = Cast<AEQScorpion>(TryGetPawnOwner());
	if(Scorpion != nullptr)
	{
		Scorpion->BaseFsm->MeleeAttackCheck();
	}
}

void UEQEnemyAnim::AnimNotify_DieEnd()
{
	IsDieDone = true;
}

void UEQEnemyAnim::AnimNotify_MushAttack()
{
	AEQMush* Mush = Cast<AEQMush>(TryGetPawnOwner());
	if(Mush != nullptr)
	{
		Mush->BaseFsm->MeleeAttackCheck();
	}
}

void UEQEnemyAnim::AnimNotify_BK_Dodge()
{
	AEQBerserkerOrc* BerserkerOrc = Cast<AEQBerserkerOrc>(TryGetPawnOwner());
	if(BerserkerOrc != nullptr)
	{
		FVector SelfPos = BerserkerOrc->GetActorLocation();
		FVector DodgePos = SelfPos + FVector(-0.000221,0,0);
		BerserkerOrc->SetActorLocation(DodgePos);
	}
}

void UEQEnemyAnim::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UEQEnemyAnim, State);
	
}
