


#include "AI/EQBaseFSM.h"

#include "AIController.h"
#include "EQEnemyPool.h"
#include "NavigationSystem.h"
#include "Animation/EQEnemyAnim.h"
#include "Character/EQCharacterBase.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


UEQBaseFSM::UEQBaseFSM()
{

	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}



void UEQBaseFSM::BeginPlay()
{
	Super::BeginPlay();
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
	Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Target != nullptr)
	{
		
		SetState(EMonsterState::Move);
	}
}

void UEQBaseFSM::TickMove() {}

void UEQBaseFSM::TickAttack() {}

void UEQBaseFSM::TickHit()
{
	Self->PlayAnimMontage(AnimMontage, 1, FName("Hit"));
	AActor* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		AI->MoveToLocation(PlayerLocation);
		SetState(EMonsterState::Attack);
	}
	Self->bCanShowHP = true;
}

void UEQBaseFSM::TickDie()
{
	CurrentTime += GetWorld()->GetDeltaSeconds();
	
	Self->PlayAnimMontage(AnimMontage,1,FName("Died"));
	
	Self->SetActorEnableCollision(ECollisionEnabled::NoCollision);
	if(CurrentTime>DieTime)
	{
		Pool->ReturnEnemyToPool(Self);
		UE_LOG(LogTemp,Warning,TEXT("BackToPool"));
		SetState(EMonsterState::Idle);
	}
}



void UEQBaseFSM::ShootWeb() {}

void UEQBaseFSM::ScorpionPrj() {}



void UEQBaseFSM::SetState(EMonsterState Next)
{
	if(Next == EMonsterState::Move)
	{
		
		UpdateRandLoc(Self->GetActorLocation(),500,RandomLoc);
	
	}
	AnimInst->State = Next;
	State = Next;
	CurrentTime = 0;
}

bool UEQBaseFSM::UpdateRandLoc(FVector OldLoc, float Radius, FVector& NewLoc)
{
	
	auto NS = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation Location;
	bool Result = NS->GetRandomReachablePointInRadius(OldLoc,Radius,Location);
	if(Result == true)
	{
		NewLoc = Location.Location;
		return true;
	}
	else
	{
		return UpdateRandLoc(OldLoc,Radius,NewLoc);
	}
}





