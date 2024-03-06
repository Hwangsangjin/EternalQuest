// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentStat.h"

#include "EQComponentInventory.h"
#include "EternalQuest.h"
#include "Net/UnrealNetwork.h"
#include "Game/EQGameSingleton.h"
#include "Character/EQCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Save/EQSaveGame.h"

UEQComponentStat::UEQComponentStat()
	: CurrentLevel(1)
{
	static ConstructorHelpers::FClassFinder<UEQSaveGame> SaveGameRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/SaveGame/BP_EQSaveGame.BP_EQSaveGame_C'"));
	if (SaveGameRef.Succeeded()) SaveGameFactory = SaveGameRef.Class;
}

void UEQComponentStat::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentHp);
	DOREPLIFETIME(ThisClass, MaxHp);
	DOREPLIFETIME(ThisClass, CurrentExp);
	DOREPLIFETIME(ThisClass, MaxExp);
	DOREPLIFETIME_CONDITION(ThisClass, BaseStat, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ThisClass, ModifierStat, COND_OwnerOnly);
}

void UEQComponentStat::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevelStat(CurrentLevel);
	ResetStat();

	OnStatChanged.AddUObject(this, &ThisClass::SetNewMaxHp);
	OnStatChanged.AddUObject(this, &ThisClass::SetNewMaxExp);

	SetIsReplicated(true);
}

void UEQComponentStat::ReadyForReplication()
{
	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::ReadyForReplication();

	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("End"));
}

void UEQComponentStat::BeginPlay()
{
	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	Super::BeginPlay();
	
}

float UEQComponentStat::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}

void UEQComponentStat::ApplyStat(const FEQCharacterStat& NewBaseStat, const FEQCharacterStat& NewModifierStat)
{
	const float MovementSpeed = (NewBaseStat + NewModifierStat).MovementSpeed;
	Player->GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

void UEQComponentStat::SetLevelStat(int32 InNewLevel)
{
	CurrentLevel = FMath::Clamp(InNewLevel, 1, UEQGameSingleton::Get().CharacterMaxLevel);
	SetBaseStat(UEQGameSingleton::Get().GetCharacterStat(CurrentLevel));
	check(BaseStat.MaxHp > 0.0f);
}

void UEQComponentStat::SetNewMaxHp(const FEQCharacterStat& InBaseStat, const FEQCharacterStat& InModifierStat)
{
	float PrevMaxHp = MaxHp;
	MaxHp = GetTotalStat().MaxHp;
	if (PrevMaxHp != MaxHp)
	{
		OnHpChanged.Broadcast(CurrentHp, MaxHp);
	}
}

void UEQComponentStat::ResetStat()
{
	SetLevelStat(CurrentLevel);
	MaxHp = BaseStat.MaxHp;
	SetHp(MaxHp);
	MaxExp = BaseStat.MaxExp;
	SetExp(MaxExp);
}

void UEQComponentStat::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChanged.Broadcast(CurrentHp, MaxHp);
}

void UEQComponentStat::SetNewMaxExp(const FEQCharacterStat& InBaseStat, const FEQCharacterStat& InModifierStat)
{
	float PrevMaxExp = MaxExp;
	MaxExp = GetTotalStat().MaxExp;
	if (PrevMaxExp != MaxExp)
	{
		OnExpChanged.Broadcast(CurrentExp, MaxExp);
	}
}

void UEQComponentStat::SetExp(float ExpAmount)
{
	CurrentExp = CurrentExp + ExpAmount;
	SetLevelStat(CurrentLevel++);

	//OnExpChanged.Broadcast(CurrentExp, MaxExp);
}

void UEQComponentStat::OnRep_CurrentHp()
{
	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	OnHpChanged.Broadcast(CurrentHp, MaxHp);

	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
}

void UEQComponentStat::OnRep_MaxHp()
{
	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	OnHpChanged.Broadcast(CurrentHp, MaxHp);
}

void UEQComponentStat::OnRep_CurrentExp()
{
	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	OnExpChanged.Broadcast(CurrentExp, MaxExp);

	if (CurrentExp >= MaxExp)
	{
		SetLevelStat(CurrentLevel++);
	}
}

void UEQComponentStat::OnRep_MaxExp()
{
	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	OnExpChanged.Broadcast(CurrentExp, MaxExp);
}

void UEQComponentStat::OnRep_BaseStat()
{
	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	OnStatChanged.Broadcast(BaseStat, ModifierStat);
}

void UEQComponentStat::OnRep_ModifierStat()
{
	EQ_SUBLOG(LogEternalQuest, Log, TEXT("%s"), TEXT("Begin"));

	OnStatChanged.Broadcast(BaseStat, ModifierStat);
}