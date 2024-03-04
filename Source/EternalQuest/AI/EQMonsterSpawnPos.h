
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQMonsterSpawnPos.generated.h"

UCLASS()
class ETERNALQUEST_API AEQMonsterSpawnPos : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQMonsterSpawnPos();

protected:
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	FVector GetSpawnPos(int32 Idx);
	int GetArrayNum() const;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(MakeEditWidget = "true"))
	TArray<FVector> SpawnPositions;

};
