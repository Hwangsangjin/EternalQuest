


#include "AI/EQBaseFSM.h"

#include "AIController.h"
#include "EQEnemyPool.h"
#include "NavigationSystem.h"
#include "Animation/EQEnemyAnim.h"
#include "Character/EQAmbushOrc.h"
#include "Character/EQCharacterBase.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


UEQBaseFSM::UEQBaseFSM()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UEQBaseFSM::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Self = Cast<AEQNormalEnemy>(GetOwner());
	AI = Cast<AAIController>(Self->GetController());
	BasicSpeed = Self->GetCharacterMovement()->MaxWalkSpeed = 100;
	AnimInst = Cast<UEQEnemyAnim>(Self->GetMesh()->GetAnimInstance());
	SetIsReplicated(true);
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
	ServerRPC_TickHit();
}

void UEQBaseFSM::TickDie()
{
	ServerRPC_TickDie();
}

void UEQBaseFSM::PlayerDie()
{
	// TArray<AActor*> AllPlayers;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEQCharacterPlayer::StaticClass(), AllPlayers);
	// for(int32 i = 0; i<AllPlayers.Num(); i++)
	// {
	// 	Target = Cast<AEQCharacterPlayer>(AllPlayers[i]);
	// 	if(Target->GetStatComponent()->CurrentHp == 0)
	// 	{
	// 		SetState(EMonsterState::Move);
	// 	}
	// }
}


void UEQBaseFSM::ShootWeb() {}

void UEQBaseFSM::ShootArrow() {}

void UEQBaseFSM::ScorpionPrj() {}

void UEQBaseFSM::WarlockPrj() {}

void UEQBaseFSM::WarlockTeleport() {}

void UEQBaseFSM::SetState(EMonsterState Next)
{
	ServerRPC_SetState(Next);
}

bool UEQBaseFSM::UpdateRandLoc(FVector OldLoc, float Radius, FVector& NewLoc)
{
	auto NS = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation Location;
	auto Result = NS->GetRandomReachablePointInRadius(OldLoc,Radius,Location);
	if(!NS)
	{
		return false;
	}
	if(Result == true)
	{
		NewLoc = Location.Location;
		return true;
	}
	//return UpdateRandLoc(OldLoc,Radius,NewLoc);
	return false;
}

void UEQBaseFSM::MeleeAttackCheck() {}


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
	//AnimInst->IsDieDone
	if(IsDieDone == false) return;
	CurrentTime += GetWorld()->GetDeltaSeconds();
	bCanAttack = false;
	if(CurrentTime>DieTime)
	{
		Target->TakeExp(Self->Experience);
		Self->DropItem();
		//SetState(EMonsterState::Idle);
		SetState(EMonsterState::Attack);
		Pool->ReturnEnemyToPool(Self);
		if(Self->IsA<AEQAmbushOrc>())
		{
			Self->Destroy();
		}
	}
}

void UEQBaseFSM::MultiRPC_TickDie_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Die"));
	FVector SoundSpawn = Self->GetMesh()->GetComponentLocation();
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),DieSound,SoundSpawn);
}


void UEQBaseFSM::ServerRPC_TickHit_Implementation()
{
	UE_LOG(LogTemp,Warning,TEXT("Hit1111111111111111111111111111111"));
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
	UE_LOG(LogTemp,Warning,TEXT("Hit222222222222222222222222222222222222222"));
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
	DOREPLIFETIME(UEQBaseFSM, bCanAttack);
	DOREPLIFETIME(UEQBaseFSM, AnimInst);
	DOREPLIFETIME(UEQBaseFSM, bIsDead);
	DOREPLIFETIME(UEQBaseFSM, SuperAmor);
	DOREPLIFETIME(UEQBaseFSM, Pool);
	DOREPLIFETIME(UEQBaseFSM, IsDieDone);
	
}



