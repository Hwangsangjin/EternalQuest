


#include "Projectile/EQAmbushTrigger.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Character/EQAmbushOrc.h"
#include "Character/EQCharacterPlayer.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"


AEQAmbushTrigger::AEQAmbushTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger -> SetupAttachment(RootComponent);
	Trigger -> SetBoxExtent(FVector(32.f,200.f,32.f));

	SpawnLoc1 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLoc1"));
	SpawnLoc1 -> SetupAttachment(Trigger);
	SpawnLoc1 -> SetRelativeLocation(FVector(-300.f,130.f,0.f));
	SpawnLoc2 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLoc2"));
	SpawnLoc2 -> SetupAttachment(Trigger);
	SpawnLoc2 -> SetRelativeLocation(FVector(-300.f,-50.f,0.f));
	SpawnLoc3 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLoc3"));
	SpawnLoc3 -> SetupAttachment(Trigger);
	SpawnLoc3 -> SetRelativeLocation(FVector(-300.f,-270.f,0.f));

	bReplicates = true;
}


void AEQAmbushTrigger::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Trigger->OnComponentBeginOverlap.AddDynamic(this,&AEQAmbushTrigger::OverLapBegin);
}




void AEQAmbushTrigger::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ServerRPC_OverLapBegin(OtherActor);
}

void AEQAmbushTrigger::ServerRPC_OverLapBegin_Implementation(AActor* OtherActor)
{
	if(OtherActor -> IsA<AEQCharacterPlayer>() && IsOverlapped == false)
	{
		const FTransform SpawnPoint1 = SpawnLoc1->GetComponentTransform();
		const FTransform SpawnPoint2 = SpawnLoc2->GetComponentTransform();
		const FTransform SpawnPoint3 = SpawnLoc3->GetComponentTransform();
		GetWorld()->SpawnActor<AEQAmbushOrc>(OrcFactory,SpawnPoint1);
		GetWorld()->SpawnActor<AEQAmbushOrc>(OrcFactory,SpawnPoint2);
		GetWorld()->SpawnActor<AEQAmbushOrc>(OrcFactory,SpawnPoint3);
		IsOverlapped = true;
	}
}


void AEQAmbushTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEQAmbushTrigger::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AEQAmbushTrigger, IsOverlapped);
	
}