// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQEnemyProjectile.generated.h"


class UEQMonsterAbility;
class AEQNormalEnemy;
class AEQCharacterPlayer;
class UNiagaraComponent;
class USphereComponent;

UCLASS()
class ETERNALQUEST_API AEQEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEQEnemyProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Niagara")
	UNiagaraComponent* NiagaraComp;

	UPROPERTY()
	AEQCharacterPlayer* Target;
	
	UPROPERTY(EditAnywhere)
	AEQNormalEnemy* Self;
	
	UPROPERTY()
	UEQMonsterAbility* MonsterAbility;

	UPROPERTY(Replicated)
	float Speed = 600;
public:

	UFUNCTION()
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
