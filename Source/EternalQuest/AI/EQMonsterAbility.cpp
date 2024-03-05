


#include "AI/EQMonsterAbility.h"

#include "AIController.h"
#include "EQBaseFSM.h"
#include "Character/EQBerserkerOrc.h"
#include "Character/EQBossEnemy.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQNormalEnemy.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Widget/EQDamageAmoutUI.h"


UEQMonsterAbility::UEQMonsterAbility()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UEQMonsterAbility::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	Target = Cast<AEQCharacterPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this,&UEQMonsterAbility::TakeDamage);
		if(Owner->IsA<AEQBossEnemy>())
		{
			GetWorld()->GetTimerManager().SetTimer(RecoveryTimerHandle,this,&UEQMonsterAbility::StaminaRecovery,1.0f,true);
		}
	}
}

void UEQMonsterAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckCanDodge();
}



void UEQMonsterAbility::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                   AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp,Warning,TEXT("CurrentHP : %f"),CurrentHealth);
	UE_LOG(LogTemp,Warning,TEXT("MaxHP : %f"), MaxHealth);
	if(Damage <= 0)
	{
		return;
	}
	UpdateHP(-Damage);
	if(auto Monster = Cast<AEQCharacterEnemy>(DamagedActor))
	{
		Monster->DamageComp->SetVisibility(true);
		DamageUI->ShowDamageAmount(Damage);
	}
	
	if(DamagedActor->IsA<AEQNormalEnemy>())
	{
		auto Monster = Cast<AEQNormalEnemy>(DamagedActor);
		HitCount ++;
		if(HitCount == 3)
		{
			Monster->BaseFsm->SuperAmor = true;	
		}
		if(CurrentHealth > 0)
		{
			if(Monster->HasAuthority())
			{
				Monster->BaseFsm->AI->StopMovement();
				if(Monster->BaseFsm->SuperAmor == false)
				{
					Monster->BaseFsm->SetState(EMonsterState::Hit);
				}
			}
		}
		else
		{
			Monster->BaseFsm->bIsDead = true;
			Monster->BaseFsm->MultiRPC_TickDie();
			Monster->SetActorEnableCollision(ECollisionEnabled::NoCollision);
			Monster->BaseFsm->SetState(EMonsterState::Die);
		}
	}
	if(DamagedActor->IsA<AEQBossEnemy>())
	{
		SaveDamage(Damage);
		if(CurrentHealth <= 0)
		{
			GetWorld()->GetGameInstance()->GetTimerManager().ClearTimer(RecoveryTimerHandle);
			IsDead = true;
			auto Orc = Cast<AEQBerserkerOrc>(DamagedActor);
			Orc->SetActorEnableCollision(ECollisionEnabled::NoCollision);
			Target->TakeExp(Orc->Experience);
			Orc->MultiRPC_Die();
			FTimerHandle DieTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(DieTimerHandle, [Orc]()
			{
				//Orc->Destroy();
			}, 5.0f, false);
		}
		else
		{
			IsDead = false;
		}
	}
}

void UEQMonsterAbility::UpdateHP(float UpdateHealth)
{
	ServerRPC_UpdateHP(UpdateHealth);
}

void UEQMonsterAbility::StaminaRecovery()
{
	// 체력증가
	float RecoveryRate = 0.003f;
	// 현재 체력이 최대 체력보다 작을 때만 회복 수행
	if (CurrentHealth < MaxHealth)
	{
		// 초당 체력 회복량 계산 및 적용
		float RecoveryAmount = MaxHealth * RecoveryRate;
		CurrentHealth += RecoveryAmount;
		// 최대 체력을 넘지 않도록 보정
		CurrentHealth = FMath::Min(CurrentHealth, MaxHealth);
	}
}


void UEQMonsterAbility::SaveDamage(float Damage)
{
	DamageReceiver += Damage;
	
	if(GetWorld()->GetTimerManager().IsTimerActive(DamageTimerHandle))
	{
		GetWorld()->GetGameInstance()->GetTimerManager().ClearTimer(DamageTimerHandle);
	}
	GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(DamageTimerHandle,this,&UEQMonsterAbility::CheckCanDodge,3.0f,false);
}

void UEQMonsterAbility::CheckCanDodge()
{
	if(DamageReceiver >= 100.f)
	{
		bIsDamageOver = true;
	}
	else
	{
		bIsDamageOver = false;
	}
}


void UEQMonsterAbility::ServerRPC_UpdateHP_Implementation(float UpdateHealth)
{
	CurrentHealth = FMath::Max(0,CurrentHealth+UpdateHealth);
	bIsHit = true;
}

void UEQMonsterAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( UEQMonsterAbility, MaxHealth);
	DOREPLIFETIME( UEQMonsterAbility, CurrentHealth);
	DOREPLIFETIME(UEQMonsterAbility, SpiderWebDamage);
	DOREPLIFETIME(UEQMonsterAbility,MushAttackDamage);
	DOREPLIFETIME(UEQMonsterAbility,ScorpionAttackDamage);
	DOREPLIFETIME(UEQMonsterAbility,bIsHit);
	DOREPLIFETIME(UEQMonsterAbility,DamageReceiver);
	DOREPLIFETIME(UEQMonsterAbility,bIsDamageOver);
	DOREPLIFETIME(UEQMonsterAbility,IsDead);
	
}
