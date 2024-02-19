


#include "Character/EQNormalEnemy.h"

#include "EQCharacterPlayer.h"
#include "AI/EQBaseFSM.h"
#include "AI/EQMonsterAbility.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AEQNormalEnemy::AEQNormalEnemy()
{
	BaseFsm = CreateDefaultSubobject<UEQBaseFSM>("BasFSM");
	Ability = CreateDefaultSubobject<UEQMonsterAbility>("Ability");
	HPComp = CreateDefaultSubobject<UWidgetComponent>("HPComp");
	HPComp -> SetupAttachment(RootComponent);
	ConstructorHelpers::FClassFinder<UUserWidget>WidgetTemp(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_MonsterHPBar.WBP_MonsterHPBar_C'"));
	if(WidgetTemp.Succeeded())
	{
		HPComp->SetWidgetClass(WidgetTemp.Class);
		HPComp->SetDrawSize(FVector2D(150,20));
		HPComp->SetRelativeLocation(FVector(0,0,120));
		HPComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HPComp->SetVisibility(false);
		HPComp->SetCastShadow(false);
	}

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

float AEQNormalEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Ability->TakeDamage(this,DamageAmount,Type,EventInstigator,DamageCauser);

	return DamageAmount;
	
	
}

void AEQNormalEnemy::MonsterProjectileHit(AActor* OtherActor)
{
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

