


#include "AI/EQMeleeFSM.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

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
	ServerRPC_MushAttack();
	// CurrentTime += GetWorld()->GetDeltaSeconds();
	// if(CurrentTime>AttackTime)
	// {
	// 	float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	// 	{
	// 		if(Dist > AttackRange)
	// 		{
	// 			SetState(EMonsterState::Move);
	// 			
	// 		}
	// 		else
	// 		{
	// 			UE_LOG(LogTemp,Warning,TEXT("Attack!!!!!!!!!!!"));
	// 			if(Self->HasAuthority())
	// 			{
	// 				if(Self->HasAuthority())
	// 				{
	// 					AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	// 					
	// 				}
	// 			}
	// 			Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
	// 		}
	// 	}
	// 	
	// 	
	// }
	
}

void UEQMeleeFSM::TickMove()
{
	Super::TickMove();

	ServerRPC_MushMove();
	// FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	// FVector Destination = Target->GetActorLocation();
	// UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	// FPathFindingQuery Query;
	// FAIMoveRequest Req;
	// Req.SetAcceptanceRadius(100);
	// Req.SetGoalLocation(Destination);
	// if(Self->HasAuthority())
	// {
	// 	AI-> BuildPathfindingQuery(Req,Query);
	// }
	// auto Result = NaviSys->FindPathSync(Query);
	//
	// //UE_LOG(LogTemp,Warning,TEXT("%d,%f,%f"),Result.IsSuccessful(),Direction.Length(),DetectionRange);
	// if(Result.IsSuccessful() && Direction.Length() < DetectionRange)
	// {
	// 	
	// 	// 속도를 추적속도로 바꾸고
	// 	ChaseSpeed = Self->GetCharacterMovement()->MaxWalkSpeed  = 450.f;
	// 	Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	// 	if(Self->HasAuthority())
	// 	{
	// 		AI->MoveToLocation(Destination);
	// 	
	// 	}
	// }
	// else if(Result.IsSuccessful() && Direction.Length() > DetectionRange)
	// {
	// 	Self->GetCharacterMovement()->MaxWalkSpeed = BasicSpeed;
	// 	FPathFollowingRequestResult R;
	// 	// Ai는 Controller가 Server에만 있기 떄문에 Has Authority 를 사용하여 서버임을 알린다.
	// 	if(Self->HasAuthority())
	// 	{
	// 		R.Code = AI -> MoveToLocation(RandomLoc);
	// 	}
	// 	if(R != EPathFollowingRequestResult::RequestSuccessful)
	// 	{
	// 		UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
	// 		ChaseSpeed = BasicSpeed;
	// 	}
	// }
	// if(Direction.Length()<=AttackRange)
	// {
	// 	SetState(EMonsterState::Attack);
	// 	CurrentTime = AttackTime;
	// 	if(Self->HasAuthority())
	// 	{
	// 		AI->StopMovement();
	// 		
	// 	}
	// }
	
}

void UEQMeleeFSM::ServerRPC_MushMove_Implementation()
{
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FVector Destination = Target->GetActorLocation();
	UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FPathFindingQuery Query;
	FAIMoveRequest Req;
	Req.SetAcceptanceRadius(100);
	Req.SetGoalLocation(Destination);
	if(Self->HasAuthority())
	{
		AI-> BuildPathfindingQuery(Req,Query);
	}
	auto Result = NaviSys->FindPathSync(Query);

	//UE_LOG(LogTemp,Warning,TEXT("%d,%f,%f"),Result.IsSuccessful(),Direction.Length(),DetectionRange);
	if(Result.IsSuccessful() && Direction.Length() < DetectionRange)
	{
		
		// 속도를 추적속도로 바꾸고
		ChaseSpeed = Self->GetCharacterMovement()->MaxWalkSpeed  = 450.f;
		Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		if(Self->HasAuthority())
		{
			AI->MoveToLocation(Destination);
		
		}
	}
	else if(Result.IsSuccessful() && Direction.Length() > DetectionRange)
	{
		Self->GetCharacterMovement()->MaxWalkSpeed = BasicSpeed;
		FPathFollowingRequestResult R;
		// Ai는 Controller가 Server에만 있기 떄문에 Has Authority 를 사용하여 서버임을 알린다.
		if(Self->HasAuthority())
		{
			R.Code = AI -> MoveToLocation(RandomLoc);
		}
		if(R != EPathFollowingRequestResult::RequestSuccessful)
		{
			UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
			ChaseSpeed = BasicSpeed;
		}
	}
	if(Direction.Length()<=AttackRange)
	{
		SetState(EMonsterState::Attack);
		CurrentTime = AttackTime;
		if(Self->HasAuthority())
		{
			AI->StopMovement();
			
		}
	}
}

void UEQMeleeFSM::ServerRPC_MushAttack_Implementation()
{
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
				if(Self->HasAuthority())
				{
					AI->SetFocus(Target,EAIFocusPriority::Gameplay);
				}
				MultiRPC_MushAttack();
			}
		}
		
		
	}
}

void UEQMeleeFSM::MultiRPC_MushAttack_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
}




