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
	FORCEINLINE bool IsAttack() const { return bIsAttacking; }
	void AttackHitCheck();

protected:
	void Attack();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Attack();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Attack();

private:
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> AttackAction;

// Mage Attack
protected:
	void MageAttack();
	void MageAttackBegin();
	void MageAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> MageAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AEQProjectileBase> FireBall;

// Warrior Attack
protected:
	void WarriorAttack();
	void WarriorAttackBegin();
	void WarriorAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> WarriorAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> AttackHitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQCharacterComboAttackData> ComboAttackData;

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool bHasNextComboCommand = false;
};
