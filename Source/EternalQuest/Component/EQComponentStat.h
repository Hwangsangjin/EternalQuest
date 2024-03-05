// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentBase.h"
#include "Character/EQCharacterStat.h"
#include "EQComponentStat.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHpChangedDelegate, float /*CurrentHp*/, float /*MaxHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExpChangedDelegate, float /*CurrentExp*/, float /*MaxExp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FEQCharacterStat& /*BaseStat*/, const FEQCharacterStat& /*ModifierStat*/);

UCLASS()
class ETERNALQUEST_API UEQComponentStat : public UEQComponentBase
{
	GENERATED_BODY()
	
public:
	UEQComponentStat();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void InitializeComponent() override;
	virtual void ReadyForReplication() override;
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetCurrentLevel() const { return CurrentLevel; }
	FORCEINLINE void AddBaseStat(const FEQCharacterStat& InAddBaseStat) { BaseStat = BaseStat + InAddBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetBaseStat(const FEQCharacterStat& InBaseStat) { BaseStat = InBaseStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }
	FORCEINLINE void SetModifierStat(const FEQCharacterStat& InModifierStat) { ModifierStat = InModifierStat; OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat()); }

	FORCEINLINE const FEQCharacterStat& GetBaseStat() const { return BaseStat; }
	FORCEINLINE const FEQCharacterStat& GetModifierStat() const { return ModifierStat; }
	FORCEINLINE FEQCharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE void HealHp(float InHealAmount) { CurrentHp = FMath::Clamp(CurrentHp + InHealAmount, 0, GetTotalStat().MaxHp); OnHpChanged.Broadcast(CurrentHp, MaxHp); }
	FORCEINLINE float GetAttackRadius() const { return AttackRadius; }

	float ApplyDamage(float InDamage);

	void ApplyStat(const FEQCharacterStat& NewBaseStat, const FEQCharacterStat& NewModifierStat);
	void SetLevelStat(int32 InNewLevel);
	void SetNewMaxHp(const FEQCharacterStat& InBaseStat, const FEQCharacterStat& InModifierStat);
	void SetHp(float NewHp);
	void SetNewMaxExp(const FEQCharacterStat& InBaseStat, const FEQCharacterStat& InModifierStat);
	void SetExp(float ExpAmount);
	void ResetStat();

	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnExpChangedDelegate OnExpChanged;
	FOnStatChangedDelegate OnStatChanged;

protected:
	UFUNCTION()
	void OnRep_CurrentHp();

	UFUNCTION()
	void OnRep_MaxHp();

	UFUNCTION()
	void OnRep_CurrentExp();

	UFUNCTION()
	void OnRep_MaxExp();

	UFUNCTION()
	void OnRep_BaseStat();

	UFUNCTION()
	void OnRep_ModifierStat();

private:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHp, Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(ReplicatedUsing = OnRep_MaxHp, Transient, VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentExp, Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentExp;

	UPROPERTY(ReplicatedUsing = OnRep_MaxExp, Transient, VisibleInstanceOnly, Category = Stat)
	float MaxExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float AttackRadius;

	UPROPERTY(ReplicatedUsing = OnRep_BaseStat, Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	FEQCharacterStat BaseStat;

	UPROPERTY(ReplicatedUsing = OnRep_ModifierStat, Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	FEQCharacterStat ModifierStat;
};
