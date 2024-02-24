// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Component/EQComponentBase.h"
#include "EQComponentMenuManager.generated.h"

class UEQComponentInventory;
class UEQWidgetIconBar;
/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ETERNALQUEST_API UEQComponentMenuManager : public UEQComponentBase
{
	GENERATED_BODY()
	
public:
	UEQComponentMenuManager();
	// ----- Override 함수 -----
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;
	// ----- Override 함수 -----

	// ----- 함수 -----
	void CallInventory(const FInputActionValue& Value);
	void CallStatus(const FInputActionValue& Value);
	void CallSkill(const FInputActionValue& Value);
	void CallQuest(const FInputActionValue& Value);
	void CallSettings(const FInputActionValue& Value);
	void FlipFlopMouseMode(const FInputActionValue& Value);
	// ----- 함수 -----

	// ----- 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> CallInventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> MouseModeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> CallSettingsAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> CallStatusAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> CallSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> CallQuestAction;

	UPROPERTY()
	TObjectPtr<UEQComponentInventory> EQComponentInventory;
	
	bool bMouseModeFlag = false;
	// ----- 변수 -----
};
