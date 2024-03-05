


#include "AI/EQMonsterSpawnPos.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"


AEQMonsterSpawnPos::AEQMonsterSpawnPos()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}


void AEQMonsterSpawnPos::BeginPlay()
{
	Super::BeginPlay();
	
}


void AEQMonsterSpawnPos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AEQMonsterSpawnPos::GetSpawnPos(int32 Idx)
{
	return SpawnPositions[Idx];
}

int AEQMonsterSpawnPos::GetArrayNum() const
{
	return SpawnPositions.Num();
}

