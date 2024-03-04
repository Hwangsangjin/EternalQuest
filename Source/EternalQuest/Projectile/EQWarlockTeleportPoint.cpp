
#include "Projectile/EQWarlockTeleportPoint.h"

// Sets default values
AEQWarlockTeleportPoint::AEQWarlockTeleportPoint()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void AEQWarlockTeleportPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEQWarlockTeleportPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AEQWarlockTeleportPoint::GetTeleportPoint(int32 Idx)
{
	return TPPoints[Idx];
}





