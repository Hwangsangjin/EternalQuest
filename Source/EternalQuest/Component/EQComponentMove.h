// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentBase.h"
#include "EQComponentMove.generated.h"

class UInputComponent;
struct FInputActionValue;
class UInputAction;

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

// Jump
protected:
	void Jump(const FInputActionValue& Value);
	void StopJumping(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Jump();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Jump();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> ParkourMontage;

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
public:
	FORCEINLINE bool IsSprinting() const { return bIsSprinting; }

protected:
	void Sprint(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Sprint(const FInputActionValue& Value);

	UFUNCTION(Client, Reliable)
	void Client_Sprint(const FInputActionValue& Value);

	void StopSprinting(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StopSprinting(const FInputActionValue& Value);

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_StopSprinting(const FInputActionValue& Value);

	void ResetFieldOfView();

private:
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> SprintAction;

	float CurrentFieldOfView = 90.0f;
	FTimerHandle SprintTimerHandle;

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
