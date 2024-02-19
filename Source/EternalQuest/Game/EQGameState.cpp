// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EQGameState.h"
#include "EternalQuest.h"

void AEQGameState::HandleBeginPlay()
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::HandleBeginPlay();

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
}

void AEQGameState::OnRep_ReplicatedHasBegunPlay()
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::OnRep_ReplicatedHasBegunPlay();

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
}
