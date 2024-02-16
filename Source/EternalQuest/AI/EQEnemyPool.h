

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQEnemyPool.generated.h"

class AEQNormalEnemy;
class AEQSpider;
class AEQMush;


UCLASS()
class ETERNALQUEST_API AEQEnemyPool : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQEnemyPool();

protected:
	
	virtual void BeginPlay() override;
public:	
	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void SpawnEnemy(const FVector& SpawnLocation);

public:
	UPROPERTY(EditDefaultsOnly,Category="Pool")
	TSubclassOf<AEQNormalEnemy> EnemyFactory;

	UPROPERTY(EditAnywhere,Category="pool")
	TMap<TSubclassOf<AEQNormalEnemy>,int32> EnemyMap;

	TArray<AEQNormalEnemy*> EnemyPool;

	void InitPool();
	int32 PoolSize;
	AEQNormalEnemy* GetInActiveEnemy();
	void ReturnEnemyToPool(AEQNormalEnemy* Enemy);
	
};
