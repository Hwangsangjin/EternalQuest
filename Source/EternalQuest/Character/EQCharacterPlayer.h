// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterBase.h"
#include "Interface/EQInterfaceAnimationAttack.h"
#include "Interface/EQInterfaceCharacterWidget.h"
#include "EQCharacterPlayer.generated.h"

struct FStreamableHandle;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAnimMontage;
class UInputComponent;
class UBoxComponent;
class UEQComponentBase;
class UEQComponentMove;
class UEQComponentInteraction;
class UEQComponentMenuManager;
class UEQComponentInventory;
class UEQComponentAttack;
class UEQComponentStat;
class UEQComponentWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FInputSignature, UInputComponent*)

UCLASS(config = EternalQuest)
class ETERNALQUEST_API AEQCharacterPlayer : public AEQCharacterBase, public IEQInterfaceAnimationAttack, public IEQInterfaceCharacterWidget
{
	GENERATED_BODY()

public:
	AEQCharacterPlayer();

	FInputSignature InputSignature;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Owner() override;
	virtual void OnRep_PlayerState() override;
	virtual void PostNetInit() override;
	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual void StopJumping() override;

// Controller
protected:
	void SetPlayerController();

// Mesh
protected:
	void UpdatePlayerMesh();
	void PlayerMeshLoadCompleted();

	UPROPERTY(config)
	TArray<FSoftObjectPath> PlayerMeshes;

	TSharedPtr<FStreamableHandle> PlayerMeshHandle;

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
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// Dead
protected:
	virtual void SetDead();
	void PlayDeadAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DeadMontage;

// UI Widget
protected:
	virtual void SetupCharacterWidget(UEQWidgetBase* InWidgetBase) override;

// Component
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentMove> MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentInteraction> InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentInventory> InventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentMenuManager> MenuManagerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentAttack> AttackComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentStat> StatComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentWidget> UserNameComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentWidget> HpBarComp;
};
