

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EQBaseFSM.generated.h"
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
	UPROPERTY(EditAnywhere,Category="Monster")
	EMonsterState State;

	UPROPERTY(EditAnywhere,Category="Monster")
	AEQNormalEnemy* Self;

	UPROPERTY(EditAnywhere,Category="Monster")
	AAIController* AI;

	UPROPERTY(EditAnywhere,Category="Monster")
	AEQCharacterPlayer* Target;

	UPROPERTY(EditAnywhere,Category="Animation")
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	UEQEnemyAnim* AnimInst;

protected:
	float CurrentTime = 0;
	float AttackTime = 2.0f;
	float AttackRange;
	float ChaseSpeed = 800;
	float BasicSpeed;
	float DetectionRange = 450;
	float DieTime = 2.0f;
	FVector RandomLoc;
	
	

protected:
	void TickIdle();
	virtual void TickMove();
	virtual void TickAttack();
	virtual void TickHit();
	virtual void TickDie();
	


public:
	virtual void ShootWeb();
	virtual void ScorpionPrj();
	void SetState(EMonsterState Next);
	bool UpdateRandLoc(FVector OldLoc, float Radius, FVector& NewLoc);
};
