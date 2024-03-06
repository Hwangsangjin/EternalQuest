


#include "Character/EQNormalEnemy.h"

#include "EQCharacterPlayer.h"
#include "AI/EQBaseFSM.h"
#include "AI/EQMonsterAbility.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Widget/EQNormalMonsterHPBar.h"


AEQNormalEnemy::AEQNormalEnemy()
{
	BaseFsm = CreateDefaultSubobject<UEQBaseFSM>("BasFSM");
	HPComp = CreateDefaultSubobject<UWidgetComponent>("HPComp");
	HPComp -> SetupAttachment(RootComponent);
	ConstructorHelpers::FClassFinder<UEQNormalMonsterHPBar>WidgetTemp(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_MonsterHPBar.WBP_MonsterHPBar_C'"));
	if(WidgetTemp.Succeeded())
	{
		HPComp->SetWidgetClass(WidgetTemp.Class);
		HPComp->SetDrawSize(FVector2D(150,50));
		HPComp->SetRelativeLocation(FVector(0,0,120));
		HPComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HPComp->SetVisibility(false);
		HPComp->SetCastShadow(false);
	}
	MonsterName = TEXT("Default Monster Name");
	bIsActive = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bReplicates = true;
	SetReplicateMovement(true);
}


void AEQNormalEnemy::ActivateEnemy(const FVector& SpawnLocation)
{
	SetActorLocation(SpawnLocation);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	bIsActive = true;
}

bool AEQNormalEnemy::IsActive()
{
	return bIsActive;
}

void AEQNormalEnemy::Deactivate()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	bIsActive = false;
}

FString AEQNormalEnemy::SetName()
{
	return MonsterName;
}


void AEQNormalEnemy::MonsterProjectileHit(AActor* OtherActor) {}

void AEQNormalEnemy::BeginPlay()
{
	Super::BeginPlay();
	SetName();
}

void AEQNormalEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto Player = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	float Dist = FVector::Dist(Player->GetActorLocation(),this->GetActorLocation());
	FVector Start = HPComp->GetComponentLocation();
	FVector Target = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0)->GetCameraLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Start,Target);
	HPComp->SetWorldRotation(NewRotation);
	if(Dist < DetectRange || bCanShowHP == true ) HPComp->SetVisibility(true);
	else  HPComp->SetVisibility(false);
}

void AEQNormalEnemy::DieEffect()
{
	// bool DieStart = true;
	// bool DieEnd = false;
	// bool VisibilityLerp = FMath::Lerp(DieStart,DieEnd,CheckTime*0.5);
	// GetMesh()->SetVisibility(VisibilityLerp);
	
}




void  AEQNormalEnemy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEQNormalEnemy, bIsActive);
	
	
}