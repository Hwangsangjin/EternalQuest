// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetLogin.h"
#include "Components/Button.h"
#include "Game/EQGameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

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
		Button_Host->OnHovered.AddDynamic(this, &ThisClass::HostButtonHovered);
		Button_Host->OnUnhovered.AddDynamic(this, &ThisClass::HostButtonUnhovered);
	}

	if (Button_Join)
	{
		Button_Join->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
		Button_Join->OnHovered.AddDynamic(this, &ThisClass::JoinButtonHovered);
		Button_Join->OnUnhovered.AddDynamic(this, &ThisClass::JoinButtonUnhovered);
		
	}

	if (Button_Mage)
	{
		Button_Mage->OnClicked.AddDynamic(this, &ThisClass::MageButtonClicked);
		Button_Mage->OnHovered.AddDynamic(this, &ThisClass::MageButtonHovered);
		Button_Mage->OnUnhovered.AddDynamic(this, &ThisClass::MageButtonUnhovered);
	}

	if (Button_Warrior)
	{
		Button_Warrior->OnClicked.AddDynamic(this, &ThisClass::WarriorButtonClicked);
		Button_Warrior->OnHovered.AddDynamic(this, &ThisClass::WarriorButtonHovered);
		Button_Warrior->OnUnhovered.AddDynamic(this, &ThisClass::WarriorButtonUnhovered);
	}

	if (Button_Cancel)
	{
		Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::UEQWidgetLogin::CloseCharacterSelect);
	}

	return true;
}

void UEQWidgetLogin::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEQWidgetLogin::NativeDestruct()
{
	LoginSetoff();
	Super::NativeDestruct();
}

void UEQWidgetLogin::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	LoadingCurrTime += InDeltaTime;
	
	if (LoadingCurrTime > 0.5)
	{
		LoadingCurrTime = 0;
		LoadingEffect();
	}
	
	if (BtnMageHovered) MageButtonHovered();
	else MageButtonUnhovered();

	if (BtnWarriorHovered) WarriorButtonHovered();
	else WarriorButtonUnhovered();

	if (BtnHostHovered) HostButtonHovered();
	else HostButtonUnhovered();

	if (BtnJoinHovered) JoinButtonHovered();
	else JoinButtonUnhovered();
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
	GameInstance->SetClassType(EClassType::ECT_Mage);

	Button_Mage->SetBackgroundColor(FLinearColor(0.411765f, 0.8f, 0.941177f, 1.0f));
	Button_Warrior->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.8f));

	if (bIsCreateSession)
	{
		GameInstance->CreateSession(NumPublicConnections, MatchType);
	}
	else
	{
		GameInstance->FindSessions(100000);
	}
	FTimerHandle EQHandle;
	GetWorld()->GetTimerManager().SetTimer(EQHandle,this, &ThisClass::CloseLoadingBorder, 6, false, 3);
	Border_Loading->SetVisibility(ESlateVisibility::Visible);
	Button_Mage->SetIsEnabled(false);
	Button_Warrior->SetIsEnabled(false);
	Button_Cancel->SetIsEnabled(false);
}

void UEQWidgetLogin::MageButtonHovered()
{
	BtnMageHovered = true;
	BtnMageScale = FMath::FInterpTo(BtnMageScale, 1.3f, GetWorld()->GetDeltaSeconds(), 3);
	Button_Mage->SetRenderScale(FVector2D(BtnMageScale));
}

void UEQWidgetLogin::MageButtonUnhovered()
{
	BtnMageHovered = false;
	BtnMageScale = FMath::FInterpTo(BtnMageScale, 1.0f, GetWorld()->GetDeltaSeconds(), 3);
	Button_Mage->SetRenderScale(FVector2D(BtnMageScale));
}

void UEQWidgetLogin::WarriorButtonClicked()
{
	GameInstance->SetClassType(EClassType::ECT_Warrior);

	Button_Warrior->SetBackgroundColor(FLinearColor(0.780392f, 0.611765f, 0.431373f, 1.0f));
	Button_Mage->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.8f));

	if (bIsCreateSession)
	{
		GameInstance->CreateSession(NumPublicConnections, MatchType);
	}
	else
	{
		GameInstance->FindSessions(100000);
	}

	Border_Loading->SetVisibility(ESlateVisibility::Visible);
	FTimerHandle EQHandle;
	GetWorld()->GetTimerManager().SetTimer(EQHandle,this, &ThisClass::CloseLoadingBorder, 6, false, 3);
	Button_Mage->SetIsEnabled(false);
	Button_Warrior->SetIsEnabled(false);
	Button_Cancel->SetIsEnabled(false);
}

void UEQWidgetLogin::WarriorButtonHovered()
{
	BtnWarriorHovered = true;
	BtnWarriorScale = FMath::FInterpTo(BtnWarriorScale, 1.3f, GetWorld()->GetDeltaSeconds(), 3);
	Button_Warrior->SetRenderScale(FVector2D(BtnWarriorScale));
}

void UEQWidgetLogin::WarriorButtonUnhovered()
{
	BtnWarriorHovered = false;
	BtnWarriorScale = FMath::FInterpTo(BtnWarriorScale, 1.0f, GetWorld()->GetDeltaSeconds(), 3);
	Button_Warrior->SetRenderScale(FVector2D(BtnWarriorScale));
}

void UEQWidgetLogin::LoadingEffect()
{
	if (Txt_Loading->GetText().ToString().Contains(TEXT("...")))
	{
		Txt_Loading->SetText(FText::FromString(FString::Printf(TEXT("로딩 중"))));
	}
	else
	{
		auto DotText = FString(TEXT("."));
		Txt_Loading->SetText(FText::FromString(FString::Printf(TEXT("%s"), *(Txt_Loading->GetText().ToString() + DotText))));
	}
}

void UEQWidgetLogin::CloseLoadingBorder()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Magenta, TEXT("세션이 없습니다."));
	Border_Loading->SetVisibility(ESlateVisibility::Hidden);
	Button_Mage->SetIsEnabled(true);
	Button_Warrior->SetIsEnabled(true);
	Button_Cancel->SetIsEnabled(true);
}

void UEQWidgetLogin::HostButtonClicked()
{
	Button_Host->SetIsEnabled(false);
	OpenCharacterSelect();
	bIsCreateSession = true;
}

void UEQWidgetLogin::HostButtonHovered()
{
	BtnHostHovered = true;
	BtnHostScale = FMath::FInterpTo(BtnHostScale, 1.3f, GetWorld()->GetDeltaSeconds(), 3);
	Button_Host->SetRenderScale(FVector2D(BtnHostScale));
}

void UEQWidgetLogin::HostButtonUnhovered()
{
	BtnHostHovered = false;
	BtnHostScale = FMath::FInterpTo(BtnHostScale, 1.0f, GetWorld()->GetDeltaSeconds(), 3);
	Button_Host->SetRenderScale(FVector2D(BtnHostScale));
}

void UEQWidgetLogin::JoinButtonClicked()
{
	Button_Join->SetIsEnabled(false);
	
	OpenCharacterSelect();
	bIsCreateSession = false;
}

void UEQWidgetLogin::JoinButtonHovered()
{
	BtnJoinHovered = true;
	BtnJoinScale = FMath::FInterpTo(BtnJoinScale, 1.3f, GetWorld()->GetDeltaSeconds(), 3);
	Button_Join->SetRenderScale(FVector2D(BtnJoinScale));
}

void UEQWidgetLogin::JoinButtonUnhovered()
{
	BtnJoinHovered = false;
	BtnJoinScale = FMath::FInterpTo(BtnJoinScale, 1.0f, GetWorld()->GetDeltaSeconds(), 3);
	Button_Join->SetRenderScale(FVector2D(BtnJoinScale));
}

void UEQWidgetLogin::OpenCharacterSelect()
{
	Blur_CharacterSelect->SetVisibility(ESlateVisibility::Visible);
}

void UEQWidgetLogin::CloseCharacterSelect()
{
	Button_Host->SetIsEnabled(true);
	Button_Join->SetIsEnabled(true);
	Blur_CharacterSelect->SetVisibility(ESlateVisibility::Hidden);
}

void UEQWidgetLogin::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString(TEXT("Session created successfully")));
		}*/

		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(PathToLevel);
		}
	}
	else
	{
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString(TEXT("Failed to create session")));
		}*/

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
			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, FString::Printf(TEXT("Id: %s, User: %s"), *Id, *User));
			}*/

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

			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Connect String: %s"), *Address));
			}*/

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
