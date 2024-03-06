


#include "AI/EQEnemySpawnManager.h"

#include "EngineUtils.h"
#include "EQBaseFSM.h"
#include "EQEnemyPool.h"
#include "EQMonsterSpawnPos.h"
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
		//FVector SpawnPoint = this->GetActorLocation();
		//FVector RandomLoc = FVector(FMath::RandRange(-1500.f,1500.f),FMath::RandRange(-1500.f,1500.f),0.f);
		FVector RandomLoc = MakeRandomSpawnPos();
		if(PoolActor == nullptr)
		{
			
			GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEQEnemySpawnManager::Spawn,SpawnTime,false);
			return;
		}
		// 월드 안에 랜덤한 위치에 스폰한다.
		PoolActor->ActivateEnemy(RandomLoc);//+SpawnPoint);
		GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&AEQEnemySpawnManager::Spawn,SpawnTime,false);
	}
	
}
void AEQEnemySpawnManager::Spawn()
{
	SeverRPC_Spawn();
}

int32 PrevIdx = -1;
FVector AEQEnemySpawnManager::MakeRandomSpawnPos()
{
	
	int32 RandIdx = FMath::RandRange(0,SpawnPos->GetArrayNum()-1);
	//중복을 막는다.
	while(PrevIdx == RandIdx)
	{
		RandIdx ++;
		if(RandIdx>=SpawnPos->GetArrayNum())
		{
			RandIdx = 0;
		}
	}
	FVector NewLocation = SpawnPos->GetSpawnPos(RandIdx);
	return NewLocation;
}





