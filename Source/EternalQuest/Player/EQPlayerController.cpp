// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/EQPlayerController.h"

void AEQPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
}
