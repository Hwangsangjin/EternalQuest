


#include "AI/EQBaseFSM.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "Animation/EQAnimInstance.h"
#include "Character/EQCharacterBase.h"
#include "Character/EQMush.h"
#include "Character/EQNormalEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"


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
	AnimInst = Cast<UEQAnimInstance>(Self->GetMesh()->GetAnimInstance());
	
}

void UEQBaseFSM::InitializeComponent()
{
	Super::InitializeComponent();
	
	
	
}



void UEQBaseFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (State)
	{
	case EMonsterState::Idle : TickIdle(); break;
	case EMonsterState::Move : TickMove(); break;
	case EMonsterState::Attack : TickAttack(); break;
	}

	
}

void UEQBaseFSM::TickIdle()
{
	

	Target = Cast<ACharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Target != nullptr)
	{
		
		SetState(EMonsterState::Move);
	}
}

void UEQBaseFSM::TickMove()
{
	
	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FVector Destination = Target->GetActorLocation();
	UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FPathFindingQuery Query;
	FAIMoveRequest Req;
	Req.SetAcceptanceRadius(50);
	Req.SetGoalLocation(Destination);
	AI-> BuildPathfindingQuery(Req,Query);
	auto Result = NaviSys->FindPathSync(Query);
	
	if(Result.IsSuccessful() && Direction.Length() < 800.f )
	{
		ChaseSpeed = Self->GetCharacterMovement()->MaxWalkSpeed  = 450.f;
		Self->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
		AI->MoveToLocation(Destination);
		CurrentTime = AttackTime;
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

void UEQBaseFSM::TickAttack()
{
	CurrentTime += GetWorld()->GetDeltaSeconds();
	float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
	if(CurrentTime>AttackTime)
	{
		if(Dist > AttackRange)
		{
			
			SetState(EMonsterState::Move);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Attack!!!!!!!!!!!"));
			SetState(EMonsterState::Move);
		}
	}
}



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



