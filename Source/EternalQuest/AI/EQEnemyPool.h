

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

	
	AEQNormalEnemy* GetPooledMonster();
	void ReturnToPool(AEQMush* ReturnMush);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pool")
	TMap<TSubclassOf<AEQNormalEnemy>,int32> Pool;
	
	UPROPERTY(EditAnywhere,Category="MonsterPool")
	float SpawnInterval;

	FTimerHandle TimerHandle;
public:
	UPROPERTY(EditAnywhere,Category="MonsterPool")
	TSubclassOf<AEQMush> PooledMushClass;
};
