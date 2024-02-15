

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQEnemySpawnManager.generated.h"

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


private:
	FTimerHandle SpawnTimerHandle;
	float SpawnTime = 3.f;
	

public:
	void Spawn();
	

	
	
};
