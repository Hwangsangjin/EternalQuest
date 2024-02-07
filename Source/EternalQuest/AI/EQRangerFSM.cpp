


#include "AI/EQRangerFSM.h"

#include "AITypes.h"
#include "NavigationSystem.h"
#include "Character/EQNormalEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"

void UEQRangerFSM::BeginPlay()
{
	Super::BeginPlay();
	AttackRange = 1100;
}

void UEQRangerFSM::TickMove()
{
	Super::TickMove();
	
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FVector Destination = Target->GetActorLocation();
	UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FPathFindingQuery Query;
	FAIMoveRequest Req;
	Req.SetAcceptanceRadius(50);
	Req.SetGoalLocation(Destination);
	AI-> BuildPathfindingQuery(Req,Query);
	auto Result = NaviSys->FindPathSync(Query);
	
	if(Result.IsSuccessful() && Direction.Length() < 1000.f)
	{
		ChaseSpeed = Self->GetCharacterMovement()->MaxWalkSpeed  = 350.f;
		Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		AI->MoveToLocation(Destination);
		SetState(EMonsterState::Attack);
	}
	else
	{
		Self->GetCharacterMovement()->MaxWalkSpeed = BasicSpeed;
		FPathFollowingRequestResult R;
		// Ai는 Controller가 Server에만 있기 떄문에 Has Authority 를 사용하여 서버임을 알린다.
		R.Code = AI -> MoveToLocation(RandomLoc);
		if(R != EPathFollowingRequestResult::RequestSuccessful)
		{
			UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
			ChaseSpeed = BasicSpeed;
			
		}
	}
	
}


void UEQRangerFSM::TickAttack()
{
	Super::TickAttack();

	DrawDebugSphere(GetWorld(),Self->GetActorLocation(),AttackRange,100,FColor::Blue);
	
	CurrentTime += GetWorld()->GetDeltaSeconds();
	// 공격 시간이되면
	if(CurrentTime > AttackTime)
	{
		// 플레이어와 애너미의 거리를 구해서
		float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
		// 만약 그 거리가 공격가능범위보다 길면
		if(Dist > AttackRange)
		{
			// Move로 전이
			SetState(EMonsterState::Move);
			
			
		}
		// 그거리가 공격가능 범위보다 짧다면
		else
		{
			AI->SetFocus(Target,EAIFocusPriority::Gameplay);
			AI->StopMovement();
			// 공격을한다.
			UE_LOG(LogTemp,Warning,TEXT("RangeAttack"));
			Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
			// 거미줄 소환
			
		}
	}
}
