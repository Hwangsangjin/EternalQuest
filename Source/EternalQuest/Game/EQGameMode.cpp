// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EQGameMode.h"
#include "Game/EQGameInstance.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

AEQGameMode::AEQGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/Blueprints/Player/BP_PlayerController.BP_PlayerController_C"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

void AEQGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		if (GEngine)
		{
			const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
			GEngine->AddOnScreenDebugMessage(1, 60.0f, FColor::Yellow, FString::Printf(TEXT("Player in game: %d"), NumberOfPlayers));

			const APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				const FString PlayerName = PlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, FString::Printf(TEXT("%s has joined the game"), *PlayerName));
			}
		}
	}
}

void AEQGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	const APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		if (GEngine)
		{
			const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
			GEngine->AddOnScreenDebugMessage(1, 60.0f, FColor::Yellow, FString::Printf(TEXT("Player in game: %d"), NumberOfPlayers - 1));

			const FString PlayerName = PlayerState->GetPlayerName();
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, FString::Printf(TEXT("%s has exited the game"), *PlayerName));
		}
	}
}
