

#include "Projectile/EQSpiderWeb.h"

#include "AI/EQMonsterAbility.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQSpider.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


AEQSpiderWeb::AEQSpiderWeb()
{
 	
	PrimaryActorTick.bCanEverTick = true;
}


void AEQSpiderWeb::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto Temp = UGameplayStatics::GetActorOfClass(GetWorld(),AEQSpider::StaticClass());
	Self = Cast<AEQSpider>(Temp);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AEQSpiderWeb::OverLapBegin);
}


void AEQSpiderWeb::Tick(float DeltaTime)
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



void AEQSpiderWeb::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	Self->MonsterProjectileHit(OtherActor);
	this->Destroy();
}
