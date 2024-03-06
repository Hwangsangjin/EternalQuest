

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EQMonsterAbility.generated.h"


class UEQReturnTimer;
class AEQCharacterPlayer;
class UEQDamageAmoutUI;
class AEQBerserkerOrc;
class UEQBossMonsterHPUI;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALQUEST_API UEQMonsterAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UEQMonsterAbility();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	UEQBossMonsterHPUI* BossMonsterHPUI;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	UEQDamageAmoutUI* DamageUI;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AEQCharacterPlayer* Target;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Monster")
	float MaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Monster")
	float CurrentHealth;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Spider")
	float SpiderWebDamage = 10.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Mush")
	float MushAttackDamage = 8.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Scorpion")
	float ScorpionAttackDamage = 25.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Orc")
	float OrcArrowDamage = 15.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Orc")
	float OrcAxeDamage = 13.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Orc")
	float OrcKnifeDamage = 9.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Orc")
	float OrcSkillDamage = 10.f;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEQReturnTimer> TimerFactory;
	UPROPERTY()
	UEQReturnTimer* ReturnTimer;

	
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Berserker")
	float BerserkerBasicAttackDamage = 10.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Berserker")
	float BerserkerComboAttackDamage_1 = 10.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Berserker")
	float BerserkerComboAttackDamage_2 = 15.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Berserker")
	float BerserkerComboAttackDamage_3 = 20.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Replicated,Category="Berserker")
	float BerserkerSmashDamage = 50.f;
	
	FTimerHandle RecoveryTimerHandle;
	float RecoveryInterval = 1.5f;
	UPROPERTY(EditAnywhere,Replicated,Category="AI")
	bool bIsHit = false;
	UPROPERTY(EditAnywhere,Replicated,Category="AI")
	float DamageReceiver;
	UPROPERTY(EditAnywhere,Replicated,Category="AI")
	bool bIsDamageOver = false;	
	FTimerHandle DamageTimerHandle;
	UPROPERTY(EditAnywhere,Replicated)
	bool IsDead = false;
	UPROPERTY(Replicated)
	int32 HitCount = 0;

public:
	void UpdateHP(float UpdateHealth);
	void StaminaRecovery();
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(Server,Reliable)
	void ServerRPC_UpdateHP(float UpdateHealth);
	
	float CurrentTime = 0;
	float DieTime = 5.0f;
	
	// TODO : 데미지가 3초동안 100이상이 들어오면
	void SaveDamage(float Damage);
	void CheckCanDodge();

	void ShowReturnCount();
	int32 TimeCount = 11.f;
	void DecreaseCount();
	FTimerHandle TimeCountHandle;
	
};
