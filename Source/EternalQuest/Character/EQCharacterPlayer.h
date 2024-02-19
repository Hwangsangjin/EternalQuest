// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterBase.h"
#include "Interface/EQInterfaceAnimationAttack.h"
#include "EQCharacterPlayer.generated.h"

class UEQComponentMenuManager;
class UEQComponentInventory;
class UEQComponentBase;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAnimMontage;
class UInputComponent;
class UBoxComponent;
class UEQComponentMove;
class UEQComponentAttack;
class UEQComponentInteraction;

DECLARE_MULTICAST_DELEGATE_OneParam(FInputSignature, UInputComponent*)

UCLASS()
class ETERNALQUEST_API AEQCharacterPlayer : public AEQCharacterBase, public IEQInterfaceAnimationAttack
{
	GENERATED_BODY()
	
public:
	AEQCharacterPlayer();

	FInputSignature InputSignature;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual void StopJumping() override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Owner() override;
	virtual void BeginPlay() override;

// Camera
public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

// Interaction Box
public:
	FORCEINLINE UEQComponentMove* GetMoveComponent() const { return MoveComp; }
	FORCEINLINE UBoxComponent* GetInteractionBox() const { return InteractionBox; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> InteractionBox;

// Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

// Attack Hit
protected:
	virtual void AttackHitCheck() override;

// Take Damage
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// Dead
protected:
	virtual void SetDead();
	void PlayDeadAnimation();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DeadMontage;

// Component
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEQComponentMove> MoveComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEQComponentInteraction> InteractionComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEQComponentInventory> InventoryComp;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEQComponentMenuManager> MenuManagerComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEQComponentAttack> AttackComp;
};
