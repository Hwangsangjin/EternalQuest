// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EQProjectileBase.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;

UCLASS()
class ETERNALQUEST_API AEQProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEQProjectileBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trigger, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Niagara, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraComponent> Niagara;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
};
