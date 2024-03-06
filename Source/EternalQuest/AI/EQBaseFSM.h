

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Iris/ReplicationSystem/RepTag.h"
#include "EQBaseFSM.generated.h"
class UEQMonsterAbility;
class AEQEnemyPool;
class AEQCharacterPlayer;
class UEQEnemyAnim;
class UEQAnimInstance;
class AEQCharacterBase;
class AAIController;
class AEQNormalEnemy;

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Move,
	Attack,
	Hit,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALQUEST_API UEQBaseFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UEQBaseFSM();

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere,Replicated,Category="Monster")
	EMonsterState State;

	UPROPERTY(EditAnywhere,Category="Monster")
	AEQNormalEnemy* Self;

	UPROPERTY(EditAnywhere,Category="Monster")
	AAIController* AI;

	UPROPERTY(EditAnywhere,Category="Monster")
	AEQCharacterPlayer* Target;

	UPROPERTY(EditAnywhere,Category="Animation")
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere,Replicated,BlueprintReadWrite,Category="Animation")
	UEQEnemyAnim* AnimInst;

	UPROPERTY(EditAnywhere,Replicated,Category="Pool")
	AEQEnemyPool* Pool;

	UPROPERTY(EditAnywhere,Category="Ability")
	UEQMonsterAbility* Ability;


protected:
	UPROPERTY(Replicated)
	float CurrentTime = 0;
	UPROPERTY(Replicated)
	float AttackTime = 2.0f;
	UPROPERTY(Replicated)
	float AttackRange;
	UPROPERTY(Replicated)
	float ChaseSpeed = 800;
	UPROPERTY(Replicated)
	float BasicSpeed;
	UPROPERTY(Replicated)
	float DetectionRange = 450;
	UPROPERTY(Replicated)
	float DieTime = 3.0f;
	UPROPERTY(Replicated)
	FVector RandomLoc;
	UPROPERTY(Replicated)
	bool bCanAttack = true;

public:
	UPROPERTY(Replicated)
	bool IsDieDone;

	UPROPERTY(EditAnywhere)
	USoundBase* ArrowSound;
	UPROPERTY(EditAnywhere)
	USoundBase* MeleeAttackSound;
	UPROPERTY(EditAnywhere)
	USoundBase* DieSound;
	
	
public:
	UPROPERTY(Replicated)
	bool bIsDead = false;
	UPROPERTY(Replicated)
	bool SuperAmor = false;
	UPROPERTY(Replicated)
	bool WarlockDie = false;


protected:
	void TickIdle();
	virtual void TickMove();
	virtual void TickAttack();
	virtual void TickHit();
	virtual void TickDie();

	void PlayerDie();


public:
	virtual void ShootWeb();
	virtual void ShootArrow();
	virtual void ScorpionPrj();
	virtual void WarlockPrj();
	virtual void WarlockTeleport();
	void SetState(EMonsterState Next);
	bool UpdateRandLoc(FVector OldLoc, float Radius, FVector& NewLoc);
	virtual void MeleeAttackCheck();
	

	
public:
	UFUNCTION(Server,Reliable)
	void ServerRPC_TickIdle();
	UFUNCTION(Server,Reliable)
	void ServerRPC_TickHit();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_TickHit();
	UFUNCTION(Server,Reliable)
	void ServerRPC_TickDie();
	UFUNCTION(NetMulticast,Unreliable)
	void MultiRPC_TickDie();
	UFUNCTION(Server,Reliable)
	void ServerRPC_SetState(EMonsterState Next);
	
};
