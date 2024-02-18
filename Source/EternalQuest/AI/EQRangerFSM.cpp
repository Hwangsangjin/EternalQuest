


#include "AI/EQRangerFSM.h"

#include "AITypes.h"
#include "NavigationSystem.h"
#include "Character/EQNormalEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "Character/EQCharacterPlayer.h"
#include "Components/ArrowComponent.h"
#include "Projectile/EQSpiderWeb.h"

void UEQRangerFSM::BeginPlay()
{
	Super::BeginPlay();
	AttackRange = 800.f;
	BasicSpeed = 250.f;
	DetectionRange = 500.f;
}

void UEQRangerFSM::TickMove()
{
	Super::TickMove();
	
	// FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	// FVector Destination = Target->GetActorLocation();
	// UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	// FPathFindingQuery Query;
	// FAIMoveRequest Req;
	// Req.SetAcceptanceRadius(50);
	// Req.SetGoalLocation(Destination);
	// if (Self->HasAuthority())
	// {
	// 	AI-> BuildPathfindingQuery(Req,Query);
	// }
	// auto Result = NaviSys->FindPathSync(Query);
	//
	//
	// if(Result.IsSuccessful() && Direction.Length() < DetectionRange && Self->HasAuthority())
	// {
	// 	// 속도를 추적속도로 바꾸고
	// 	ChaseSpeed = Self->GetCharacterMovement()->MaxWalkSpeed  = 350.f;
	// 	Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	// 	if(Self->HasAuthority())
	// 	{
	// 		AI->MoveToLocation(Destination);
	// 	}
	// 	
	// }
	// else if(Result.IsSuccessful() == false && Direction.Length() > DetectionRange && Self->HasAuthority())
	// {
	// 	Self->GetCharacterMovement()->MaxWalkSpeed = BasicSpeed;
	// 	FPathFollowingRequestResult R;
	// 	// Ai는 Controller가 Server에만 있기 떄문에 Has Authority 를 사용하여 서버임을 알린다.
	// 	R.Code = AI -> MoveToLocation(RandomLoc);
	// 	if(R != EPathFollowingRequestResult::RequestSuccessful)
	// 	{
	// 		UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
	// 		ChaseSpeed = BasicSpeed;
	// 		
	// 	}
	// }
	// if(Direction.Length()<=AttackRange)
	// {
	// 	SetState(EMonsterState::Attack);
	// 	CurrentTime = AttackTime;
	// 	if(Self->HasAuthority())
	// 	{
	// 		AI->StopMovement();
	// 	}
	// }
	ServerRPC_SpiderMove();
	
}


void UEQRangerFSM::TickAttack()
{
	Super::TickAttack();
	ServerRPC_SpiderAttack();
	//DrawDebugSphere(GetWorld(),Self->GetActorLocation(),AttackRange,100,FColor::Blue);
	
	// CurrentTime += GetWorld()->GetDeltaSeconds();
	// // 공격 시간이되면
	// if(CurrentTime > AttackTime)
	// {
	// 	if (Target)
	// 	{
	// 		FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	// 		FRotator NewRotation = Direction.Rotation();
	// 		Self->SetActorRotation(NewRotation);
	// 		Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
	// 		CurrentTime = 0;
	// 		// 플레이어와 애너미의 거리를 구해서
	// 		float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	// 		// 만약 그 거리가 공격가능범위보다 길면
	// 		if(Dist > AttackRange)
	// 		{
	// 			// Move로 전이
	// 			SetState(EMonsterState::Move);
	// 			Self->StopAnimMontage();
	// 		}
	// 	}
	// }
}



void UEQRangerFSM::ShootWeb()
{
	Super::ShootWeb();
	if(Self->HasAuthority())
	{
		AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	}
	//FTransform ShootPoint = Self->GetArrowComponent()->GetComponentTransform();
	FTransform ShootPoint = Self->GetMesh()->GetSocketTransform(FName("WebPoint"));
	GetWorld()->SpawnActor<AEQSpiderWeb>(WebFactory,ShootPoint);
}

void UEQRangerFSM::MultiRPC_SpiderMove_Implementation()
{
	
}

void UEQRangerFSM::ServerRPC_SpiderMove_Implementation()
{
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FVector Destination = Target->GetActorLocation();
	UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FPathFindingQuery Query;
	FAIMoveRequest Req;
	Req.SetAcceptanceRadius(100);
	Req.SetGoalLocation(Destination);
	if (Self->HasAuthority())
	{
		AI-> BuildPathfindingQuery(Req,Query);
	}
	auto Result = NaviSys->FindPathSync(Query);
	
	
	if(Result.IsSuccessful() && Direction.Length() < DetectionRange && Self->HasAuthority())
	{
		// 속도를 추적속도로 바꾸고
		ChaseSpeed = Self->GetCharacterMovement()->MaxWalkSpeed  = 350.f;
		Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		if(Self->HasAuthority())
		{
			AI->MoveToLocation(Destination);
		}
		
	}
	else if(Result.IsSuccessful() == false && Direction.Length() > DetectionRange && Self->HasAuthority())
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


void UEQRangerFSM::ServerRPC_SpiderAttack_Implementation()
{
	CurrentTime += GetWorld()->GetDeltaSeconds();
	// 공격 시간이되면
	if(CurrentTime > AttackTime)
	{
		if (Target)
		{
			FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
			FRotator NewRotation = Direction.Rotation();
			Self->SetActorRotation(NewRotation);
			MultiRPC_SpiderAttack();
			CurrentTime = 0;
			// 플레이어와 애너미의 거리를 구해서
			float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
			// 만약 그 거리가 공격가능범위보다 길면
			if(Dist > AttackRange)
			{
				// Move로 전이
				SetState(EMonsterState::Move);
				//Self->StopAnimMontage();
			}
		}
	}
}
void UEQRangerFSM::MultiRPC_SpiderAttack_Implementation()
{
	
	//DrawDebugSphere(GetWorld(),Self->GetActorLocation(),AttackRange,100,FColor::Blue);
	Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
	UE_LOG(LogTemp,Warning,TEXT("ClientSpiderrAttack!!!!!!!!!!!!!!!!!!!"));
}



