


#include "AI/EQMeleeFSM.h"

#include "Character/EQNormalEnemy.h"

void UEQMeleeFSM::TickAttack()
{
	Super::TickAttack();

	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime>AttackTime)
	{
		CurrentTime += GetWorld()->GetDeltaSeconds();
		float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
		if(CurrentTime>AttackTime)
		{
			if(Dist > AttackRange)
			{
			
				SetState(EMonsterState::Move);
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("Attack!!!!!!!!!!!"));
			}
		
		
		}
	}
}
