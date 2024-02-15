// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetIconBar.generated.h"

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
	
	virtual void NativeConstruct() override;
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
	UButton* Btn_Settings;

	UPROPERTY()
	AEQPlayerController* EQPlayerController;
	// ----- Flag -----

	void ClearIconFlag();
	bool bOpenStatus = false;
	bool bOpenInventory = false;
	bool bOpenSkill = false;
	bool bOpenQuest = false;
	bool bOpenSettings = false;
	// ----- Flag -----
};
