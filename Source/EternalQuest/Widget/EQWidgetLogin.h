// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "EQWidgetLogin.generated.h"

class UButton;
class UEQGameInstance;

UCLASS()
class ETERNALQUEST_API UEQWidgetLogin : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void LoginSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString LobbyPath = FString(TEXT("/Game/Maps/GameMap")));

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

private:
	void LoginSetoff();

// Session
public:
	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

protected:
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);

	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

private:
	TObjectPtr<UEQGameInstance> GameInstance;

	int32 NumPublicConnections{ 4 };
	FString MatchType{ TEXT("FreeForAll") };
	FString PathToGame{ TEXT("") };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Host;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Join;

// Character Class
public:
	UFUNCTION()
	void MageButtonClicked();

	UFUNCTION()
	void WarriorButtonClicked();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Mage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Warrior;
};
