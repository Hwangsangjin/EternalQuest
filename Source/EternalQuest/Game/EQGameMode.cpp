// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EQGameMode.h"
#include "EternalQuest.h"
#include "Player/EQPlayerController.h"
#include "Player/EQPlayerState.h"
#include "Game/EQGameState.h"
#include "Game/EQGameInstance.h"

AEQGameMode::AEQGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Blueprints/Character/BP_Player.BP_Player_C"));
	if (DefaultPawnClassRef.Succeeded())
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/EternalQuest.EQPlayerController"));
	if (PlayerControllerClassRef.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	GameStateClass = AEQGameState::StaticClass();
	PlayerStateClass = AEQPlayerState::StaticClass();

	bUseSeamlessTravel = true;
}

void AEQGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("====="));
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
}

APlayerController* AEQGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));

	return NewPlayerController;
}

void AEQGameMode::PostLogin(APlayerController* NewPlayer)
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostLogin(NewPlayer);

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ClientConnections.Num() == 0)
		{
			EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("No Client Connection"));
		}
		else
		{
			for (const auto& Connection : NetDriver->ClientConnections)
			{
				EQ_LOG(LogEternalQuest, Log, TEXT("Client Connections: %s"), *Connection->GetName());
			}
		}
	}
	else
	{
		EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("No NetDriver"));
	}

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));

	/*if (GameState)
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
	}*/
}

void AEQGameMode::StartPlay()
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::StartPlay();

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
}

void AEQGameMode::Logout(AController* Exiting)
{
	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::Logout(Exiting);

	EQ_LOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));

	/*const APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		if (GEngine)
		{
			const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
			GEngine->AddOnScreenDebugMessage(1, 60.0f, FColor::Yellow, FString::Printf(TEXT("Player in game: %d"), NumberOfPlayers - 1));

			const FString PlayerName = PlayerState->GetPlayerName();
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, FString::Printf(TEXT("%s has exited the game"), *PlayerName));
		}
	}*/
}
