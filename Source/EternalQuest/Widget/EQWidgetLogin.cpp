// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetLogin.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Game/EQGameInstance.h"
#include "Game/EQGameMode.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

void UEQWidgetLogin::LoginSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LevelPath)
{
	PathToLevel = FString::Printf(TEXT("%s?listen"), *LevelPath);
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	GameInstance = Cast<UEQGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		GameInstance->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
		GameInstance->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		GameInstance->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		GameInstance->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	}
}

bool UEQWidgetLogin::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (Button_Host)
	{
		Button_Host->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}

	if (Button_Join)
	{
		Button_Join->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}

	if (Button_Mage)
	{
		Button_Mage->OnClicked.AddDynamic(this, &ThisClass::MageButtonClicked);
	}

	if (Button_Warrior)
	{
		Button_Warrior->OnClicked.AddDynamic(this, &ThisClass::WarriorButtonClicked);
	}

	return true;
}

void UEQWidgetLogin::NativeDestruct()
{
	LoginSetoff();
	Super::NativeDestruct();
}

void UEQWidgetLogin::LoginSetoff()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

void UEQWidgetLogin::MageButtonClicked()
{
	if (GameInstance->GetWorld()->GetFirstPlayerController()->HasAuthority())
	{
		GameInstance->SetClassType(EClassType::ECT_Mage);
	}
	else
	{
		GameInstance->SetClassType(EClassType::ECT_Mage);
	}

	Button_Mage->SetBackgroundColor(FLinearColor(0.411765f, 0.8f, 0.941177f, 1.0f));
	Button_Warrior->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.8f));
}

void UEQWidgetLogin::WarriorButtonClicked()
{
	if (GameInstance->GetWorld()->GetFirstPlayerController()->HasAuthority())
	{
		GameInstance->SetClassType(EClassType::ECT_Warrior);
	}
	else
	{
		GameInstance->SetClassType(EClassType::ECT_Warrior);
	}

	Button_Warrior->SetBackgroundColor(FLinearColor(0.780392f, 0.611765f, 0.431373f, 1.0f));
	Button_Mage->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.8f));
}

void UEQWidgetLogin::HostButtonClicked()
{
	Button_Host->SetIsEnabled(false);
	GameInstance->CreateSession(NumPublicConnections, MatchType);
}

void UEQWidgetLogin::JoinButtonClicked()
{
	Button_Join->SetIsEnabled(false);
	GameInstance->FindSessions(100000);
}

void UEQWidgetLogin::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString(TEXT("Session created successfully")));
		}

		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(PathToLevel);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("Failed to create session")));
		}

		Button_Host->SetIsEnabled(true);
	}
}

void UEQWidgetLogin::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (!GameInstance)
	{
		return;
	}

	for (const FOnlineSessionSearchResult& Result : SessionResults)
	{
		const FString Id = Result.GetSessionIdStr();
		const FString User = Result.Session.OwningUserName;
		FString SettingsValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingsValue);

		if (SettingsValue == MatchType)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("Id: %s, User: %s"), *Id, *User));
			}

			GameInstance->JoinSession(Result);
			return;
		}
	}

	if (!bWasSuccessful || SessionResults.Num() == 0)
	{
		Button_Join->SetIsEnabled(true);
	}
}

void UEQWidgetLogin::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Connect String: %s"), *Address));
			}

			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}

	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		Button_Join->SetIsEnabled(true);
	}
}

void UEQWidgetLogin::OnDestroySession(bool bWasSuccessful)
{
}

void UEQWidgetLogin::OnStartSession(bool bWasSuccessful)
{
}
