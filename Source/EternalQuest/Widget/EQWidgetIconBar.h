// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetIconBar.generated.h"

class UEQComponentMenuManager;
class AEQPlayerController;
class UButton;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetIconBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetIconBar(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	// ----- 함수 -----
	UFUNCTION()
	void OnHoverStatus();

	UFUNCTION()
	void OnUnhoverStatus();

	UFUNCTION()
	void OnClickStatus();

	UFUNCTION()
	void OnHoverInventory();

	UFUNCTION()
	void OnUnhoverInventory();

	UFUNCTION()
	void OnClickInventory();

	UFUNCTION()
	void OnHoverSkill();

	UFUNCTION()
	void OnUnhoverSkill();

	UFUNCTION()
	void OnClickSkill();

	UFUNCTION()
	void OnHoverQuest();

	UFUNCTION()
	void OnUnhoverQuest();

	UFUNCTION()
	void OnClickQuest();

	UFUNCTION()
	void OnHoverPostBox();

	UFUNCTION()
	void OnUnhoverPostBox();

	UFUNCTION()
	void OnClickPostBox();
	
	UFUNCTION()
	void OnHoverSettings();

	UFUNCTION()
	void OnUnhoverSettings();

	UFUNCTION()
	void OnClickSettings();
	// ----- 함수 -----
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UButton* Btn_Status;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UButton* Btn_Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UButton* Btn_Skill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UButton* Btn_Quest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UButton* Btn_PostBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UButton* Btn_Settings;

	UPROPERTY()
	AEQPlayerController* EQPlayerController;

	UPROPERTY()
	UEQComponentMenuManager* MenuManager;
	
	// ----- Flag -----

	void ClearIconFlag();
	bool bOpenStatus = false;
	bool bOpenInventory = false;
	bool bOpenSkill = false;
	bool bOpenQuest = false;
	bool bOpenPostBox = false;
	bool bOpenSettings = false;
	// ----- Flag -----

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundWave> UIOpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundWave> UICloseSound;
};
