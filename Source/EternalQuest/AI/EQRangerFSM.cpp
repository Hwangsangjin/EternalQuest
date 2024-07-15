


#include "AI/EQRangerFSM.h"

#include "AITypes.h"
#include "NavigationSystem.h"
#include "Character/EQNormalEnemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
//#include "AssetTypeActions/AssetDefinition_SoundBase.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQSpider.h"
#include "Components/ArrowComponent.h"
#include "Item/EQItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/EQRangerOrcArrow.h"
#include "Projectile/EQSpiderWeb.h"

void UEQRangerFSM::BeginPlay()
{
	Super::BeginPlay();
	AttackRange = 800.f;
	BasicSpeed = 250.f;
	DetectionRange = 500.f;
	SetIsReplicated(true);
}

void UEQRangerFSM::TickMove()
{
	Super::TickMove();
	if(!Self->HasAuthority()) return;
	MultiRPC_Move();
	TArray<AActor*> AllPlayer;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AEQCharacterPlayer::StaticClass(),AllPlayer);
	float Dist = 10000;
	for(int32 i = 0; i<AllPlayer.Num(); i++)
	{
		float TempDist = FVector::Dist(AllPlayer[i]->GetActorLocation(),Self->GetActorLocation());
		
		if(Dist > TempDist)
		{
			Dist = TempDist;
			Target = Cast<AEQCharacterPlayer>(AllPlayer[i]);
		}
	}

	if (!Target)
	{
		return;
	}

	FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
	FVector Destination = Target->GetActorLocation();
	UNavigationSystemV1* NaviSys = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FPathFindingQuery Query;
	FAIMoveRequest Req;
	Req.SetAcceptanceRadius(50);
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
	else if(Result.IsSuccessful() == false || Direction.Length() > DetectionRange && Self->HasAuthority())
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


void UEQRangerFSM::TickAttack()
{
	ServerRPC_SpiderAttack();
}



void UEQRangerFSM::ShootWeb()
{
	Super::ShootWeb();
	if(Self->HasAuthority())
	{
		AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	}
	FTransform ShootPoint = Self->GetMesh()->GetSocketTransform(FName("WebPoint"));
	GetWorld()->SpawnActor<AEQSpiderWeb>(PrjFactory,ShootPoint);
}

void UEQRangerFSM::ShootArrow()
{
	Super::ShootArrow();
	
	if(Self->HasAuthority())
	{
		AI->SetFocus(Target,EAIFocusPriority::Gameplay);
	}
	MultiRPC_ShootArrow();
	FTransform ShootPoint = Self->GetMesh()->GetSocketTransform(FName("ArrowPoint"));
	GetWorld()->SpawnActor<AEQRangerOrcArrow>(PrjFactory,ShootPoint);
}

void UEQRangerFSM::MultiRPC_Move_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Move"));
}

void UEQRangerFSM::MultiRPC_ShootArrow_Implementation()
{
	FVector SpawnSound = Self->GetMesh()->GetComponentLocation();
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ArrowSound,SpawnSound);
}


void UEQRangerFSM::ServerRPC_SpiderAttack_Implementation()
{
	bCanAttack = true;
	CurrentTime += GetWorld()->GetDeltaSeconds();
	// 공격 시간이되면
	if(CurrentTime > AttackTime && bCanAttack == true)
	{
		if (Target)
		{
			FVector Direction = Target->GetActorLocation() - Self->GetActorLocation();
			FRotator NewRotation = Direction.Rotation();
			Self->SetActorRotation(NewRotation);
			MultiRPC_SpiderAttack();
			CurrentTime = 0;
			float Dist = FVector::Dist(Target->GetActorLocation(),Self->GetActorLocation());
			if(Dist > AttackRange)
			{
				
				SetState(EMonsterState::Move);
				Self->StopAnimMontage();
			}
		}
	}
}
void UEQRangerFSM::MultiRPC_SpiderAttack_Implementation()
{
	Self->PlayAnimMontage(AnimMontage,1,FName("Attack"));
	FVector SpawnSound = Self->GetMesh()->GetComponentLocation();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),ArrowSound,SpawnSound);
}



