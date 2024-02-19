// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQScorpionFSM.h"

#include "AIController.h"
#include "AITypes.h"
#include "EQMonsterAbility.h"
#include "NavigationSystem.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Projectile/EQScorpionSkill.h"


void UEQScorpionFSM::BeginPlay()
{
	Super::BeginPlay();
	
	DetectionRange = 2000.f;
	AttackTime = 2.0f;
	BasicSpeed = 300.f;
	
}

void UEQScorpionFSM::TickMove()
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
   
	if(Result.IsSuccessful() && Direction.Length() < DetectionRange && Self->HasAuthority())
	{
		ChaseSpeed = Self->GetCharacterMovement()->MaxWalkSpeed = 400.f;
		AI->MoveToLocation(Target->GetActorLocation());
		//UE_LOG(LogTemp,Warning,TEXT("%f"),ChaseSpeed);
		Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		if(Direction.Length() < MinRangeAttackRange)
		{
			SetState(EMonsterState::Attack);
			CurrentTime = AttackTime;
		}
	}
	// 플레이어와거리가 탐지 범위보다 작을때  
	else if(Result.IsSuccessful() || Direction.Length() > DetectionRange && Self->HasAuthority())
	{
      
		Self->GetCharacterMovement()->MaxWalkSpeed = BasicSpeed;
		FPathFollowingRequestResult R;
		// Ai는 Controller가 Server에만 있기 떄문에 Has Authority 를 사용하여 서버임을 알린다.
		R.Code = AI -> MoveToLocation(RandomLoc);
		if(R != EPathFollowingRequestResult::RequestSuccessful)
		{
			UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
			ChaseSpeed = BasicSpeed;
			//   UE_LOG(LogTemp,Warning,TEXT("%f"),ChaseSpeed);
		}
	}

}

void UEQScorpionFSM::TickAttack()
{
	Super::TickAttack();
	// DrawDebugSphere(GetWorld(),Self->GetActorLocation(),MeleeAttackRange,100,FColor::Green);
	// DrawDebugSphere(GetWorld(),Self->GetActorLocation(),MinRangeAttackRange,100,FColor::Red);
	// DrawDebugSphere(GetWorld(),Self->GetActorLocation(),MaxRangeAttackRange,100,FColor::White);

	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime > AttackTime && Target != nullptr)
	{
		CheckPlayerLoc();
	}
}

void UEQScorpionFSM::TickDie()
{
	Super::TickDie();
	ServerRPC_ScorpionDie();
}

void UEQScorpionFSM::MeleeAttackCheck()
{
	Super::MeleeAttackCheck();
	FHitResult HitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack),false,Self);
	float MeleeRange = 100.f;
	float MeleeAttackRad = 50.f;
	float Damage = 10;
	FVector StartLoc = Self->GetActorLocation() + Self->GetActorForwardVector() * Self->GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + Self->GetActorForwardVector() * MeleeRange;

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult,StartLoc,EndLoc,FQuat::Identity,ECC_GameTraceChannel1,FCollisionShape::MakeSphere(MeleeAttackRad),Params);
	if(bHit)
	{
		FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(Damage,DamageEvent,nullptr,Self);
	}
}


void UEQScorpionFSM::ScorpionAttack()
{
	// AI->MoveToLocation(Target->GetActorLocation());
	// SetFocus();
	// // 근거리 공격
	// float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	// if(Dist < MeleeAttackRange)
	// {
	// 	Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
	// 	SetState(EMonsterState::Attack);
	// }
	ServerRPC_ScorpionAttack();
}

void UEQScorpionFSM::ScorpionSkill()
{
	if(!bIsUsingSkill)
	{
		UE_LOG(LogTemp,Warning,TEXT("RangeAttack!!!!!!!"));
		SetFocus();
		Self->GetCharacterMovement()->StopMovementImmediately();
		bIsUsingSkill = true;
		CurrentTime += GetWorld()->GetDeltaSeconds();
		Self->PlayAnimMontage(AnimMontage,1,FName("Skill"));
		SetState(EMonsterState::Attack);	
	}
	
}

void UEQScorpionFSM::CheckPlayerLoc()
{
	float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	if(Dist < MeleeAttackRange) ScorpionAttack();
	else if(Dist > MinRangeAttackRange && Dist < MaxRangeAttackRange) ScorpionSkill();
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
	//AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	//FTransform ShootPoint = Self->GetArrowComponent()->GetComponentTransform();
	FTransform ShootPoint = Self->GetMesh()->GetSocketTransform(FName("SkillPoint"));
	GetWorld()->SpawnActor<AEQScorpionSkill>(SkillFactory,ShootPoint);
	bIsUsingSkill = false;
}

void UEQScorpionFSM::MultiRPC_ScopionDie_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Died"));
}

void UEQScorpionFSM::ServerRPC_ScorpionDie_Implementation()
{
	CurrentTime += GetWorld()->GetDeltaSeconds();
	MultiRPC_ScopionDie();
	Self->SetActorEnableCollision(ECollisionEnabled::NoCollision);
	if(CurrentTime>DieTime)
	{
		Self->Destroy();
	}
}

void UEQScorpionFSM::ServerRPC_ScorpionAttack_Implementation()
{
	AI->MoveToLocation(Target->GetActorLocation());
	SetFocus();
	// 근거리 공격
	float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	if(Dist < MeleeAttackRange)
	{
		MultiRPC_ScorpionAttack();
		SetState(EMonsterState::Attack);
	}
}

void UEQScorpionFSM::MultiRPC_ScorpionAttack_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
	UE_LOG(LogTemp,Warning,TEXT("ScorAttack!!!!!!!!!!!!!"));

}

