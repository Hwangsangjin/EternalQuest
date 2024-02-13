// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQScorpionFSM.h"

#include "AIController.h"
#include "AITypes.h"
#include "NavigationSystem.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Projectile/EQScorpionSkill.h"


void UEQScorpionFSM::BeginPlay()
{
	Super::BeginPlay();
	
	ChaseSpeed = 1000.f;
	DetectionRange = 2000.f;
	AttackTime = 3.0f;
	
}

void UEQScorpionFSM::TickMove()
{
	Super::TickMove();
	DrawDebugSphere(GetWorld(),Self->GetActorLocation(),DetectionRange,100,FColor::Blue);
	UE_LOG(LogTemp,Warning,TEXT("TIckMove!!!!!!!!!!"));
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FVector Destination = Target->GetActorLocation();
	UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FPathFindingQuery Query;
	FAIMoveRequest Req;
	Req.SetAcceptanceRadius(50);
	Req.SetGoalLocation(Destination);
	AI-> BuildPathfindingQuery(Req,Query);
	auto Result = NaviSys->FindPathSync(Query);
	
	if(Result.IsSuccessful() && Direction.Length() < DetectionRange)
	{
		UE_LOG(LogTemp,Warning,TEXT("TIckMove11111111111111111111111111111111!!!!!!!!!!"));
		Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		//AI->MoveToLocation(Destination);
		if(Direction.Length() < MeleeAttackRange)
		{
			UE_LOG(LogTemp,Warning,TEXT("TIckMove333333333333333333333333333333333333!!!!!!!!!!"));
			SetState(EMonsterState::Attack);
			CurrentTime = AttackTime;
			AI->StopMovement();
		}
	}
	
	// 플레이어와거리가 탐지 범위보다 작을때  
	else if(Result.IsSuccessful() || Direction.Length() > DetectionRange)
	{
		UE_LOG(LogTemp,Warning,TEXT("TIckMove22222222222222222222222222222222222222!!!!!!!!!!"));
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

void UEQScorpionFSM::TickAttack()
{
	Super::TickAttack();
	
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime > AttackTime && Target != nullptr)
	{
		CheckPlayerLoc();
	}
}

void UEQScorpionFSM::TickHit()
{
	Super::TickHit();
	Self->PlayAnimMontage(AnimMontage,1,FName("Hit"));
	SetState(EMonsterState::Attack);
}

void UEQScorpionFSM::TickDie()
{
	Super::TickDie();
	CurrentTime += GetWorld()->GetDeltaSeconds();
	UE_LOG(LogTemp,Warning,TEXT("DIE!!!!!!!!!!!!!!!!!!!!!!!!!!"));
	Self->PlayAnimMontage(AnimMontage,1,FName("Died"));
	
	Self->SetActorEnableCollision(ECollisionEnabled::NoCollision);
	if(CurrentTime>DieTime)
	{
		Self->Destroy();
	}
	
}


void UEQScorpionFSM::ScorpionAttack()
{
	AI->MoveToLocation(Target->GetActorLocation());
	SetFocus();
	// 근거리 공격
	float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	if(Dist < MeleeAttackRange)
	{
		Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
		SetState(EMonsterState::Attack);
	}
}

void UEQScorpionFSM::ScorpionSkill()
{
	SetFocus();
	float RandomValue = FMath::FRand();
	if(RandomValue <= 0.6f)
	{
		UE_LOG(LogTemp,Warning,TEXT("3333333333333333333333333333333333333"));
		Self->PlayAnimMontage(AnimMontage,1,FName("Skill"));
		SetState(EMonsterState::Attack);
	}
	else
	{
		SetFocus();
		// 근거리 공격
		UE_LOG(LogTemp,Warning,TEXT("111111111111111111111111111111111111"));
		Self->SetActorLocation(Target->GetActorLocation());
		float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
		if(Dist < MeleeAttackRange)
		{
			Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
			SetState(EMonsterState::Attack);
		}
		
	}
}

void UEQScorpionFSM::CheckPlayerLoc()
{
	float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	// 플레이어와 의 거리가 근접공격 범위 보다 작을 떄 Melee Attack;
	if(Dist < MeleeAttackRange) ScorpionAttack();
	// 플레이어와 의 거리가 근접공격 보다 넓고 원거리 공격범위 보다 짧으면 RangeAttack;
	else if(Dist > MeleeAttackRange && Dist < RangeAttackRange) ScorpionSkill();
	else SetState(EMonsterState::Move);
}

void UEQScorpionFSM::SetFocus()
{
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FRotator NewRotation = Direction.Rotation();
	Self->SetActorRotation(NewRotation);
}

void UEQScorpionFSM::ScorpionPrj()
{
	Super::ScorpionPrj();
	AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	FTransform ShootPoint = Self->GetArrowComponent()->GetComponentTransform();
	GetWorld()->SpawnActor<AEQScorpionSkill>(SkillFactory,ShootPoint);
}

