// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentBase.h"
#include "EQComponentAttack.generated.h"

class UInputAction;
class UAnimMontage;
class UEQCharacterComboAttackData;
class AEQProjectileBase;
class UNiagaraSystem;

UCLASS()
class ETERNALQUEST_API UEQComponentAttack : public UEQComponentBase
{
	GENERATED_BODY()
	
public:
	UEQComponentAttack();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

// Attack
public:
	void AttackHitCheck();

protected:
	void Attack();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Attack();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Attack();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> AttackAction;

// Default Attack
public:
	FORCEINLINE bool IsAttack() const { return bIsAttacking; }

protected:
	void DefaultAttack();
	void DefaultAttackBegin();
	void DefaultAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

private:
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DefaultAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AEQProjectileBase> FireBall;

// Combo Attack
protected:
	void ComboAttack();
	void ComboAttackBegin();
	void ComboAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> ComboAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQCharacterComboAttackData> ComboAttackData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> ComboEffect;

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool bHasNextComboCommand = false;
};
