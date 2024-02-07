

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EQBaseFSM.generated.h"
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
	ACharacter* Target;

public:
	float CurrentTime = 0;
	float AttackTime = 2.0f;
	float AttackRange;
	float ChaseSpeed;
	float BasicSpeed;
	FVector RandomLoc;

protected:
	void TickIdle();
	virtual void TickMove();
	virtual void TickAttack();
	virtual void InitializeComponent() override;

public:
	virtual void ShootWeb();
	void SetState(EMonsterState Next);
	bool UpdateRandLoc(FVector OldLoc, float Radius, FVector& NewLoc);

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	UEQAnimInstance* AnimInst;
};
