// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "EQWidgetLogin.generated.h"

class UTextBlock;
class UBorder;
class UBackgroundBlur;
class UButton;
class UEQGameInstance;

UCLASS()
class ETERNALQUEST_API UEQWidgetLogin : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void LoginSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeForAll")), FString LobbyPath = FString(TEXT("/Game/Maps/VillageMap")));

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void LoginSetoff();

// Session
public:
	
	// 호스트 버튼 //
	UFUNCTION()
	void HostButtonClicked();
	UFUNCTION()
	void HostButtonHovered();
	UFUNCTION()
	void HostButtonUnhovered();
	// 호스트 버튼 //

	// 조인 버튼 //
	UFUNCTION()
	void JoinButtonClicked();
	UFUNCTION()
	void JoinButtonHovered();
	UFUNCTION()
	void JoinButtonUnhovered();
	// 조인 버튼 //

	
	UFUNCTION()
	void OpenCharacterSelect();
	
	UFUNCTION()
	void CloseCharacterSelect();
// Session End
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
	FString PathToLevel{ TEXT("") };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Host;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Join;

// Character Class
public:
	// 메이지 선택 버튼 //
	UFUNCTION()
	void MageButtonClicked();
	UFUNCTION()
	void MageButtonHovered();
	UFUNCTION()
	void MageButtonUnhovered();

	// 워리어 선택 버튼 //
	UFUNCTION()
	void WarriorButtonClicked();
	UFUNCTION()
	void WarriorButtonHovered();
	UFUNCTION()
	void WarriorButtonUnhovered();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Mage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UBackgroundBlur> Blur_CharacterSelect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UButton> Button_Cancel;

	bool bIsCreateSession = false;

	// 로딩창 UI //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UBorder> Border_Loading;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player, Meta = (BindWidget), Meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextBlock> Txt_Loading;
	
	float LoadingCurrTime;
	float BtnHostScale = 1;
	bool BtnHostHovered = false;
	float BtnJoinScale = 1;
	bool BtnJoinHovered = false;
	float BtnMageScale = 1;
	bool BtnMageHovered = false;
	float BtnWarriorScale = 1;
	bool BtnWarriorHovered = false;
	
	void LoadingEffect();
	UFUNCTION()
	void CloseLoadingBorder();
};
