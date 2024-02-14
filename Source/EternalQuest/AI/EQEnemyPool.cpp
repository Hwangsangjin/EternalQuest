


#include "AI/EQEnemyPool.h"

#include "Character/EQMush.h"
#include "Character/EQNormalEnemy.h"


AEQEnemyPool::AEQEnemyPool()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	SpawnInterval = 10.0f;

}


void AEQEnemyPool::BeginPlay()
{
	Super::BeginPlay();
	
}


void AEQEnemyPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





