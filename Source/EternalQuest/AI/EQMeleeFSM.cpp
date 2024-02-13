


#include "AI/EQMeleeFSM.h"

#include "AIController.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"

void UEQMeleeFSM::BeginPlay()
{
	Super::BeginPlay();

	AttackRange = 100;
}

void UEQMeleeFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQMeleeFSM::TickAttack()
{
	Super::TickAttack();
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime>AttackTime)
	{
		float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
		{
			if(Dist > AttackRange)
			{
				SetState(EMonsterState::Move);
				
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("Attack!!!!!!!!!!!"));
				AI->SetFocus(Target,EAIFocusPriority::Gameplay);
				Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
			}
		}
		
		
	}
	
}

void UEQMeleeFSM::TickHit()
{
	Super::TickHit();
	Self->PlayAnimMontage(AnimMontage,1,FName("Hit"));
	SetState(EMonsterState::Move);
}



