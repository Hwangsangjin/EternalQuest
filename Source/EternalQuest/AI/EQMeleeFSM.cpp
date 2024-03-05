


#include "AI/EQMeleeFSM.h"

#include "AIController.h"
#include "EQMonsterAbility.h"
#include "NavigationSystem.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQMush.h"
#include "Character/EQNormalEnemy.h"
#include "Character/EQWarriorOrc.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/EQItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

void UEQMeleeFSM::BeginPlay()
{
	Super::BeginPlay();

	AttackRange = 100.f;
	DetectionRange = 800.f;
}

void UEQMeleeFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQMeleeFSM::TickAttack()
{
	Super::TickAttack();
	//ServerRPC_MushAttack();

	if(!Self->HasAuthority()) return;
	bCanAttack = true;
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime > AttackTime && bCanAttack == true)
	{
		float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
		{
			if(Dist > AttackRange)
			{
				SetState(EMonsterState::Move);
				
			}
			else
			{
				AI->SetFocus(Target,EAIFocusPriority::Gameplay);
				SetState(EMonsterState::Attack);
				MultiRPC_MushAttack();
			}
		}
	}
}

void UEQMeleeFSM::TickMove()
{
	Super::TickMove();
	if(!Self->HasAuthority()) return;
	TArray<AActor*> allPlayer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEQCharacterPlayer::StaticClass(), allPlayer);
	float dist = 100000;
	
	for(int32 i = 0; i < allPlayer.Num(); i++)
	{
		float tempDist = FVector::Distance(allPlayer[i]->GetActorLocation(), Self->GetActorLocation());
		if(dist > tempDist)
		{
			dist = tempDist;
			Target = Cast<AEQCharacterPlayer>(allPlayer[i]);
		}
	}
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

void UEQMeleeFSM::MeleeAttackCheck()
{
	Super::MeleeAttackCheck();
	FHitResult HitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack),false,Self);
	float MeleeRange = 100.f;
	float MeleeAttackRad = 50.f;
	float Damage = 5;
	FVector StartLoc = Self->GetActorLocation() + Self->GetActorForwardVector() * Self->GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + Self->GetActorForwardVector() * MeleeRange;

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult,StartLoc,EndLoc,FQuat::Identity,ECC_GameTraceChannel1,FCollisionShape::MakeSphere(MeleeAttackRad),Params);
	if(bHit)
	{
		FDamageEvent DamageEvent;
		auto Player = Cast<AEQCharacterPlayer>(HitResult.GetActor());
		if(Player)
		{
			Player ->TakeDamage(Damage,DamageEvent,nullptr,Self);
		}
		
	}
}




void UEQMeleeFSM::ServerRPC_MushMove_Implementation()
{
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FVector Destination = Target->GetActorLocation();
	
	if(Self->HasAuthority())
	{
		UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		FPathFindingQuery Query;
		FAIMoveRequest Req;
		Req.SetAcceptanceRadius(100);
		Req.SetGoalLocation(Destination);
		AI-> BuildPathfindingQuery(Req,Query);
		auto Result = NaviSys->FindPathSync(Query);
		UE_LOG(LogTemp,Warning,TEXT("%d,%f,%f"),Result.IsSuccessful(),Direction.Length(),DetectionRange);
		if(Result.IsSuccessful() && Direction.Length() < DetectionRange)
		{
			
			
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
	bCanAttack = true;
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime > AttackTime && bCanAttack == true)
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
					SetState(EMonsterState::Attack);
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





