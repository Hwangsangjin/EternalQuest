// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Component/EQComponentBase.h"
#include "EQComponentMove.generated.h"

UCLASS()
class ETERNALQUEST_API UEQComponentMove : public UEQComponentBase
{
	GENERATED_BODY()
public:
	UEQComponentMove();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Jump
protected:
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> JumpAction;

// Move
protected:
	void Move(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> MoveAction;

// Turn
protected:
	void Turn(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> TurnAction;

// Look
protected:
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> LookAction;

// Sprint
protected:
	void Sprint(const FInputActionValue& Value);
	void StopSprinting(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> SprintAction;

	float CurrentFieldOfView = 90.0f;
	FTimerHandle SprintTimerHandle;

	bool bIsSprinting = false;

// Enter
protected:
	void Enter(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> EnterAction;

public:
	UFUNCTION(Server, Reliable)
	void ServerRPC_SendChat(const FText& InText, const FText& InPlayerName);

	UFUNCTION(Client, Reliable)
	void ClientRPC_SendChat(const FText& InText, const FText& InPlayerName);
};
