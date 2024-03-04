

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQEnemySpawnManager.generated.h"

class AEQMonsterSpawnPos;
class AEQNormalEnemy;
class AEQMush;
class AEQEnemyPool;

UCLASS()
class ETERNALQUEST_API AEQEnemySpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQEnemySpawnManager();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category="Pool")
	AEQEnemyPool* Pool;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEQNormalEnemy> EnemyType;

	UPROPERTY(EditAnywhere)
	AEQMonsterSpawnPos* SpawnPos;

private:
	FTimerHandle SpawnTimerHandle;
	float SpawnTime = 3.f;
	

public:
	UFUNCTION(Server,Reliable)
	void SeverRPC_Spawn();
	void Spawn();
	FVector MakeRandomSpawnPos();
};
