// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentBase.h"
#include "EQComponentAvoid.generated.h"

class UInputComponent;
struct FInputActionValue;
class UInputAction;

UCLASS()
class ETERNALQUEST_API UEQComponentAvoid : public UEQComponentBase
{
	GENERATED_BODY()
	
public:
	UEQComponentAvoid();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

// Avoid
public:
	FORCEINLINE bool IsAvoiding() const { return bIsAvoiding; }

	void AvoidableCheck();

protected:
	void Avoid(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Avoid();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Avoid();

private:
	bool bIsAvoiding = false;
	bool bHitDetected = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> AvoidAction;

// Roll
protected:
	void Roll();
	void RollBegin();
	void RollEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> RollMontage;

// Teleport
protected:
	void Teleport();
	void TeleportBegin();
	void TeleportEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> TeleportMontage;

	FVector_NetQuantize TeleportPoint;
};
