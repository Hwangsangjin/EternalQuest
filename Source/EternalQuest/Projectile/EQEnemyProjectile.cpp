


#include "Projectile/EQEnemyProjectile.h"

#include "NiagaraComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


AEQEnemyProjectile::AEQEnemyProjectile()
{
	
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp -> SetupAttachment(SphereComp);
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComp");
	NiagaraComp->SetupAttachment(MeshComp);
	bReplicates = true;

}


void AEQEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto Temp = UGameplayStatics::GetActorOfClass(GetWorld(),AEQNormalEnemy::StaticClass());
	Self = Cast<AEQNormalEnemy>(Temp);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AEQEnemyProjectile::OverLapBegin);
}


void AEQEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Target != nullptr)
	{
		FVector Direction = GetActorForwardVector();
		Direction.Normalize();
		FVector Velocity = Direction * Speed;
		SetActorLocation(GetActorLocation()+Velocity*DeltaTime);	
	}
}

void AEQEnemyProjectile::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AEQEnemyProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( AEQEnemyProjectile, Speed);
}