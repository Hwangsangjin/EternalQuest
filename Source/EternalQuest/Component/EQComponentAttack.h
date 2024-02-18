// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentBase.h"
#include "EQComponentAttack.generated.h"

class UInputAction;
class UAnimMontage;
class UEQCharacterComboAttackData;

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
	void Attack();
	void HitCheck();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> AttackMontage;

// Default Attack
protected:
	void DefaultAttack();
	void DefaultAttackBegin();
	void DefaultAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

private:
	bool bIsDefaultAttacking = false;

// Combo Attack
protected:
	void ComboAttack();
	void ComboAttackBegin();
	void ComboAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQCharacterComboAttackData> ComboAttackData;

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool bHasNextComboCommand = false;
};
