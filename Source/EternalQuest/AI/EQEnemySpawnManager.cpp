


#include "AI/EQEnemySpawnManager.h"

#include "EngineUtils.h"
#include "EQEnemyPool.h"
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
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEQEnemySpawnManager::Spawn,SpawnTime,false);
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
		FVector RandomLoc = FVector(FMath::RandRange(-1000,1000),FMath::RandRange(-1000,1000),0.f);
		if(PoolActor == nullptr)
		{
			UE_LOG(LogTemp,Warning,TEXT("CannotSpawn"));
			GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEQEnemySpawnManager::Spawn,SpawnTime,false);
			return;
		}
		// 월드 안에 랜덤한 위치에 스폰한다.
		PoolActor->ActivateEnemy(RandomLoc+SpawnPoint);
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEQEnemySpawnManager::Spawn,SpawnTime,false);
		UE_LOG(LogTemp,Warning,TEXT("Spawning"));
	}
	else UE_LOG(LogTemp,Warning,TEXT("NoPool!!!!!!!!!!!"));
}

void AEQEnemySpawnManager::Spawn()
{
	UE_LOG(LogTemp,Warning,TEXT("InitSpawn"));
	SeverRPC_Spawn();
}





