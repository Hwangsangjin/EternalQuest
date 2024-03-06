// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQWarlockOrcFSM.h"

#include "AIController.h"
#include "AITypes.h"
#include "EQMonsterAbility.h"
#include "NavigationSystem.h"
#include "Animation/EQEnemyAnim.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/EQDoor.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include "Projectile/EQWarlockOrcSkill.h"
#include "Projectile/EQWarlockTeleportPoint.h"


void UEQWarlockOrcFSM::BeginPlay()
{
	Super::BeginPlay();
	DetectionRange = 2000.f;
	AttackTime = 2.0f;
	BasicSpeed = 150.f;
	DieTime = 10.0f;
}

void UEQWarlockOrcFSM::TickMove()
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
		ChaseSpeed = Self->GetCharacterMovement()->MaxWalkSpeed = 200.f;
		AI->MoveToLocation(Target->GetActorLocation());
		Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		if(Direction.Length() < MaxRangeAttackRange)
		{
			SetState(EMonsterState::Attack);
			CurrentTime = AttackTime;
		}
	}
	// else if(Result.IsSuccessful() || Direction.Length() > DetectionRange && Self->HasAuthority())
	// {
	// 	Self->GetCharacterMovement()->MaxWalkSpeed = BasicSpeed;
	// 	FPathFollowingRequestResult R;
	// 	R.Code = AI -> MoveToLocation(RandomLoc);
	// 	if(R != EPathFollowingRequestResult::RequestSuccessful)
	// 	{
	// 		UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
	// 		ChaseSpeed = BasicSpeed;
	// 	}
	// }

}

void UEQWarlockOrcFSM::TickAttack()
{
	Super::TickAttack();
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if(CurrentTime > AttackTime && Target != nullptr)
	{
		CheckPlayerLoc();
	}
}

void UEQWarlockOrcFSM::MeleeAttackCheck()
{
	Super::MeleeAttackCheck();
	FHitResult HitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack),false,Self);
	float MeleeRange = 100.f;
	float MeleeAttackRad = 50.f;
	float Damage = Ability->OrcKnifeDamage;
	FVector StartLoc = Self->GetActorLocation() + Self->GetActorForwardVector() * Self->GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + Self->GetActorForwardVector() * MeleeRange;

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult,StartLoc,EndLoc,FQuat::Identity,ECC_GameTraceChannel1,FCollisionShape::MakeSphere(MeleeAttackRad),Params);
	if(bHit)
	{
		FDamageEvent DamageEvent;
		auto Player = Cast<AEQCharacterPlayer>(HitResult.GetActor());
		if(Player)
		{
			Player -> TakeDamage(Damage,DamageEvent,nullptr,Self);
		}
	}
}

void UEQWarlockOrcFSM::WarlockAttack()
{
	if(!Self->HasAuthority()) return;
	AI->MoveToLocation(Target->GetActorLocation());
	SetFocus();
	// Ability->HitCount = 0;
	//SuperAmor = true;
	float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	if(Dist < MeleeAttackRange)
	{
		MultiRPC_OrcWarlockAttack();
		SetState(EMonsterState::Attack);
	}
}

void UEQWarlockOrcFSM::WarlockSkill()
{
	if(!bIsUsingSkill)
	{
		SetFocus();
		Self->GetCharacterMovement()->StopMovementImmediately();
		bIsUsingSkill = true;
		CurrentTime += GetWorld()->GetDeltaSeconds();
		MultiRPC_OrcWarlockSkill();
		SetState(EMonsterState::Attack);
	}
}

void UEQWarlockOrcFSM::WarlockTeleport()
{
	// 피격시 맞은 위치로 이동하게 한다.
	// 텔레포트 액터에 배열에 있는 값의 위치로 이동하게 한다.
	if(TPPoint)
	{
		//Ability->HitCount = 0;
		int32 RandNum = FMath::RandRange(0,2);
		FVector NewLocation = TPPoint->GetTeleportPoint(RandNum);
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("%f,%f,%f"),NewLocation.X,NewLocation.Y,NewLocation.Z));
		Self->SetActorLocation(NewLocation);
	}
}

void UEQWarlockOrcFSM::CheckPlayerLoc()
{
	float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	if(Dist < MeleeAttackRange) WarlockAttack();
	else if(Dist > MinRangeAttackRange && Dist < MaxRangeAttackRange) WarlockSkill();
	else SetState(EMonsterState::Move);
}

void UEQWarlockOrcFSM::SetFocus()
{
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FRotator NewRotation = Direction.Rotation();
	Self->SetActorRotation(NewRotation);
}

void UEQWarlockOrcFSM::TickDie()
{
	Super::TickDie();
	if(AnimInst->IsDieDone == false) return;
	bCanAttack = false;
	bIsUsingSkill = true;
	CurrentTime += GetWorld()->GetDeltaSeconds();
	Self->SetActorEnableCollision(ECollisionEnabled::NoCollision);
	WarlockDie = true;
	Door->IsOpen = true;
	DoorOpen();
	if(CurrentTime>DieTime)
	{
		Target->TakeExp(Self->Experience);
		Door -> IsOpen = false;
		Self->DropItem();
		Self->Destroy();
	}
}


void UEQWarlockOrcFSM::WarlockPrj()
{
	Super::ScorpionPrj();
	SuperAmor = false;
	FTransform ShootPoint = Self->GetMesh()->GetSocketTransform(FName("WarlockSkillPoint"));
	GetWorld()->SpawnActor<AEQWarlockOrcSkill>(SkillFactory,ShootPoint);
	bIsUsingSkill = false;
}

void UEQWarlockOrcFSM::DoorOpen()
{
	if(Door->IsOpen == true)
	{
		FRotator TargetRotation1 = FRotator(0, 130, 0);
		FRotator CurrentRotation1 = Door->Door1->GetRelativeRotation();
		float InterpFactor = FMath::Clamp(GetWorld()->DeltaTimeSeconds / 2.0f, 0.0f, 1.0f);
		FRotator LerpedRotation1 = FMath::Lerp(CurrentRotation1, TargetRotation1, InterpFactor);
		Door->Door1->SetRelativeRotation(LerpedRotation1);
		FRotator TargetRotation2 = FRotator(0, -130, 0);
		FRotator CurrentRotation2 = Door->Door2->GetRelativeRotation();
		FRotator LerpedRotation2 = FMath::Lerp(CurrentRotation2, TargetRotation2, InterpFactor);
		Door->Door2->SetRelativeRotation(LerpedRotation2);
	}
}


void UEQWarlockOrcFSM::MultiRPC_OrcWarlockAttack_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
}

void UEQWarlockOrcFSM::MultiRPC_OrcWarlockSkill_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Skill"));
}
