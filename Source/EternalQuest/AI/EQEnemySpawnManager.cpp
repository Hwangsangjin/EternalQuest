


#include "AI/EQEnemySpawnManager.h"

#include "EngineUtils.h"
#include "EQBaseFSM.h"
#include "EQEnemyPool.h"
#include "NavigationSystem.h"
#include "Animation/EQEnemyAnim.h"
#include "Character/EQMush.h"
#include "Kismet/GameplayStatics.h"

AEQEnemySpawnManager::AEQEnemySpawnManager()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

}


void AEQEnemySpawnManager::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority())
	{
		GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEQEnemySpawnManager::Spawn,SpawnTime,false);
	}
}


void AEQEnemySpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEQEnemySpawnManager::SeverRPC_Spawn_Implementation()
{
	if(Pool)
	{
		AEQNormalEnemy* PoolActor = Pool->GetInActiveEnemy();
		FVector SpawnPoint = this->GetActorLocation();
		FVector RandomLoc = FVector(FMath::RandRange(-1500.f,1500.f),FMath::RandRange(-1500.f,1500.f),0.f);
		UNavigationSystemV1* NS = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
		// FNavLocation NavLocation;
		// if (NS->GetRandomReachablePointInRadius(RandomLoc, 1.0f, NavLocation))
		// {
			if(PoolActor == nullptr)
			{
				UE_LOG(LogTemp,Warning,TEXT("CannotSpawn"));
				GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEQEnemySpawnManager::Spawn,SpawnTime,false);
				return;
			}
			// 월드 안에 랜덤한 위치에 스폰한다.
			PoolActor->ActivateEnemy(RandomLoc+SpawnPoint);
			GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEQEnemySpawnManager::Spawn,SpawnTime,false);
			UE_LOG(LogTemp,Warning,TEXT("Spawning"));
		//}
		// else
		// {
		// 	UE_LOG(LogTemp,Warning,TEXT("NoNavMesh"));
		// }
		
	}
	else UE_LOG(LogTemp,Warning,TEXT("NoPool!!!!!!!!!!!"));
}

void AEQEnemySpawnManager::Spawn()
{
	UE_LOG(LogTemp,Warning,TEXT("InitSpawn"));
	SeverRPC_Spawn();
}





