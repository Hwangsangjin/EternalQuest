


#include "AI/EQEnemyPool.h"

#include "EQMonsterAbility.h"
#include "Character/EQMush.h"
#include "Character/EQNormalEnemy.h"


AEQEnemyPool::AEQEnemyPool()
{
	PrimaryActorTick.bCanEverTick = false;
	
}


void AEQEnemyPool::BeginPlay()
{
	Super::BeginPlay();
	InitPool();
	
}


void AEQEnemyPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEQEnemyPool::SpawnEnemy(const FVector& SpawnLocation)
{
	AEQNormalEnemy* Enemy = GetInActiveEnemy();
	if(Enemy)
	{
		Enemy->ActivateEnemy(SpawnLocation);
	}
}

void AEQEnemyPool::InitPool()
{
	for (auto& Pair : EnemyMap)
	{
		EnemyFactory= Pair.Key;
		PoolSize = Pair.Value;
		for(int i = 0; i< PoolSize; i++)
		{
			FActorSpawnParameters params;
			auto NewEnemy = GetWorld()->SpawnActor<AEQNormalEnemy>(EnemyFactory,FVector(0,0,100),FRotator::ZeroRotator);
			NewEnemy->Deactivate();
			EnemyPool.Add(NewEnemy);
			UE_LOG(LogTemp,Warning,TEXT("Added Object to the Pool"));
		}
	}
	
}

AEQNormalEnemy* AEQEnemyPool::GetInActiveEnemy()
{
	for(AEQNormalEnemy* Enemy : EnemyPool)
	{
		if(!Enemy->IsActive())
		{
			return Enemy;
		}
	}
	return nullptr;
}

void AEQEnemyPool::ReturnEnemyToPool(AEQNormalEnemy* Enemy)
{
	if(Enemy)
	{
		Enemy->Ability->CurrentHealth = 100.f;
		Enemy->Deactivate();
		UE_LOG(LogTemp,Warning,TEXT("DeactivateEnemy!!!!!!!!!!!!!!!!"));
	}
}










