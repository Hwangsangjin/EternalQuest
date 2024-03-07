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
	FORCEINLINE bool IsComboAttack() const { return bIsComboAttacking; }
	void AttackHitCheck();

private:
	bool bIsAttacking = false;
	bool bIsComboAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> LeftAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> RightAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> MageAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> WarriorAttackMontage;

// Left Attack
protected:
	void LeftAttack();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_LeftAttack();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_LeftAttack();

// Mage Left Attack
protected:
	void MageLeftAttack();
	void MageLeftAttackBegin();
	void MageLeftAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AEQProjectileBase> FireArrow;

// Warrior Left Attack
protected:
	void WarriorLeftAttack();
	void WarriorLeftAttackBegin();
	void WarriorLeftAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraSystem> WarriorAttackHitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQCharacterComboAttackData> ComboAttackData;

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool bHasNextComboCommand = false;

// Right Attack
protected:
	void RightAttack();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RightAttack();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_RightAttack();

// Mage Right Attack
protected:
	void MageRightAttack();
	void MageRightAttackBegin();
	void MageRightAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);
	void SpawnFireBall();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AEQProjectileBase> FireBall;

// Warrior Right Attack
protected:
	void WarriorRightAttack();
	void WarriorRightAttackBegin();
	void WarriorRightAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);
};
