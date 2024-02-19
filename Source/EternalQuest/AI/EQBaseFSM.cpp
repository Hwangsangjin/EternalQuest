


#include "AI/EQBaseFSM.h"

#include "AIController.h"
#include "EQEnemyPool.h"
#include "NavigationSystem.h"
#include "Animation/EQEnemyAnim.h"
#include "Character/EQCharacterBase.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


UEQBaseFSM::UEQBaseFSM()
{

	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	SetIsReplicated(true);
	
}



void UEQBaseFSM::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Self = Cast<AEQNormalEnemy>(GetOwner());
	AI = Cast<AAIController>(Self->GetController());
	BasicSpeed = Self->GetCharacterMovement()->MaxWalkSpeed = 100;
	AnimInst = Cast<UEQEnemyAnim>(Self->GetMesh()->GetAnimInstance());
}




void UEQBaseFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (State)
	{
	case EMonsterState::Idle : TickIdle(); break;
	case EMonsterState::Move : TickMove(); break;
	case EMonsterState::Attack : TickAttack(); break;
	case EMonsterState::Hit : TickHit(); break;
	case EMonsterState::Die : TickDie(); break;
	}

	
}

void UEQBaseFSM::TickIdle()
{
	// Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// if(Target != nullptr)
	// {
	// 	
	// 	SetState(EMonsterState::Move);
	// }
	ServerRPC_TickIdle();
}

void UEQBaseFSM::TickMove() {}

void UEQBaseFSM::TickAttack() {}

void UEQBaseFSM::TickHit()
{
	//Self->PlayAnimMontage(AnimMontage, 1, FName("Hit"));
	// AActor* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	// if (PlayerCharacter)
	// {
	// 	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	// 	AI->MoveToLocation(PlayerLocation);
	// 	SetState(EMonsterState::Attack);
	// }
	// Self->bCanShowHP = true;
	ServerRPC_TickHit();
}

void UEQBaseFSM::TickDie()
{
	// CurrentTime += GetWorld()->GetDeltaSeconds();
	//
	// Self->PlayAnimMontage(AnimMontage,1,FName("Died"));
	//
	// Self->SetActorEnableCollision(ECollisionEnabled::NoCollision);
	// if(CurrentTime>DieTime)
	// {
	// 	Pool->ReturnEnemyToPool(Self);
	// 	UE_LOG(LogTemp,Warning,TEXT("BackToPool"));
	// 	SetState(EMonsterState::Idle);
	// }
	ServerRPC_TickDie();
}



void UEQBaseFSM::ShootWeb() {}

void UEQBaseFSM::ScorpionPrj() {}



void UEQBaseFSM::SetState(EMonsterState Next)
{
	// if(Next == EMonsterState::Move)
	// {
	// 	
	// 	UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
	//
	// }
	// AnimInst->State = Next;
	// State = Next;
	// CurrentTime = 0;
	ServerRPC_SetState(Next);
}

bool UEQBaseFSM::UpdateRandLoc(FVector OldLoc, float Radius, FVector& NewLoc)
{
	
	auto NS = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation Location;
	auto Result = NS->GetRandomReachablePointInRadius(OldLoc,Radius,Location);
	if(Result == true)
	{
		NewLoc = Location.Location;
		return true;
	}
	else
	{
		//return UpdateRandLoc(OldLoc,Radius,NewLoc);
		return false;
	}
	
}

void UEQBaseFSM::MeleeAttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack),false,Self);
	float MeleeAttackRange = 100.f;
	float MeleeAttackRad = 50.f;
	float Damage = 0;
	FVector StartLoc = Self->GetActorLocation() + Self->GetActorForwardVector() * Self->GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + Self->GetActorForwardVector() * MeleeAttackRange;

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult,StartLoc,EndLoc,FQuat::Identity,ECC_GameTraceChannel1,FCollisionShape::MakeSphere(MeleeAttackRad),Params);
	if(bHit)
	{
		FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(Damage,DamageEvent,nullptr,Self);
	}
}


void UEQBaseFSM::ServerRPC_SetState_Implementation(EMonsterState Next)
{
	if(Next == EMonsterState::Move)
	{
		
		UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
	
	}
	AnimInst->State = Next;
	State = Next;
	CurrentTime = 0;
	
}


void UEQBaseFSM::ServerRPC_TickIdle_Implementation()
{
	Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Target != nullptr)
	{
		
		SetState(EMonsterState::Move);
	}
}

void UEQBaseFSM::ServerRPC_TickDie_Implementation()
{
	CurrentTime += GetWorld()->GetDeltaSeconds();
	Self->SetActorEnableCollision(ECollisionEnabled::NoCollision);
	if(CurrentTime>DieTime)
	{
		Pool->ReturnEnemyToPool(Self);
		UE_LOG(LogTemp,Warning,TEXT("BackToPool"));
		SetState(EMonsterState::Idle);
	}
	MultiRPC_TickDie();
}

void UEQBaseFSM::MultiRPC_TickDie_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Died"));
}


void UEQBaseFSM::ServerRPC_TickHit_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("ServerHit!!!!!!!!!!!!!!"));
	AActor* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		AI->MoveToLocation(PlayerLocation);
		SetState(EMonsterState::Attack);
	}
	Self->bCanShowHP = true;
	MultiRPC_TickHit();
}
void UEQBaseFSM::MultiRPC_TickHit_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("MultiHit!!!!!!!!!!!!!!"));
	Self->PlayAnimMontage(AnimMontage, 1, FName("Hit"));
}



void UEQBaseFSM::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEQBaseFSM, State);
	DOREPLIFETIME(UEQBaseFSM, CurrentTime);
	DOREPLIFETIME(UEQBaseFSM, AttackTime);
	DOREPLIFETIME(UEQBaseFSM, AttackRange);
	DOREPLIFETIME(UEQBaseFSM, ChaseSpeed);
	DOREPLIFETIME(UEQBaseFSM, BasicSpeed);
	DOREPLIFETIME(UEQBaseFSM, DetectionRange);
	DOREPLIFETIME(UEQBaseFSM, DieTime);
	DOREPLIFETIME(UEQBaseFSM, RandomLoc);
	
}



