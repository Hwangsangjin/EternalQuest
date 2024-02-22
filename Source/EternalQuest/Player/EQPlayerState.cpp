// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EQPlayerState.h"
#include "EternalQuest.h"

void AEQPlayerState::PostInitializeComponents()
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostInitializeComponents();

	UpdateClassType();

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
}

void AEQPlayerState::UpdateClassType()
{
	ClassType = Cast<UEQGameInstance>(GetGameInstance())->GetClassType();
}
