// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterBase.h"
#include "Game/EQGameInstance.h"
#include "Interface/EQInterfaceAnimationAttack.h"
#include "Interface/EQInterfaceAnimationSkill.h"
#include "Interface/EQInterfaceCharacterWidget.h"
#include "EQCharacterPlayer.generated.h"

struct FStreamableHandle;
struct FEQCharacterStat;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAnimMontage;
class UInputComponent;
class USceneCaptureComponent2D;
class UBoxComponent;
class UEQComponentBase;
class UEQComponentMove;
class UEQComponentAttack;
class UEQComponentSkill;
class UEQComponentStat;
class UEQComponentInteraction;
class UEQComponentMenuManager;
class UEQComponentInventory;
class UEQComponentQuest;
class UEQComponentWidget;
class UNiagaraComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FInputSignature, UInputComponent*)

UCLASS(config = EternalQuest)
class ETERNALQUEST_API AEQCharacterPlayer : public AEQCharacterBase, public IEQInterfaceAnimationAttack, public IEQInterfaceAnimationSkill, public IEQInterfaceCharacterWidget
{
	GENERATED_BODY()

public:
	AEQCharacterPlayer();

	FInputSignature InputSignature;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Owner() override;
	virtual void OnRep_PlayerState() override;
	virtual void PostNetInit() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual void StopJumping() override;
	void CreateMinimap();

// Controller
protected:
	void SetPlayerController();

// Class Type
public:
	FORCEINLINE EClassType GetClassType() const { return ClassType; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	EClassType ClassType = EClassType::ECT_None;

// Mesh
protected:
	UFUNCTION(Server, Reliable)
	void Server_UpdateClassType(EClassType InClassType);

	UFUNCTION(Client, Reliable)
	void Client_UpdateClassType(EClassType InClassType);

	void UpdateClassType();
	void CharacterMeshLoad(EClassType InClassType, AEQCharacterPlayer* CharacterPlayer);
	void BodyMeshLoadCompleted();
	void HairMeshLoadCompleted();
	void HatMeshLoadCompleted();
	void WandMeshLoadCompleted();
	void BookMeshLoadCompleted();
	void SwordMeshLoadCompleted();
	void ShieldMeshLoadCompleted();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> HairMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> HatMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> WandMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> BookMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> SwordMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> ShieldMesh;

	UPROPERTY(config)
	TArray<FSoftObjectPath> BodyMeshes;
	UPROPERTY(config)
	TArray<FSoftObjectPath> HairMeshes;
	UPROPERTY(config)
	TArray<FSoftObjectPath> HatMeshes;
	UPROPERTY(config)
	TArray<FSoftObjectPath> WandMeshes;
	UPROPERTY(config)
	TArray<FSoftObjectPath> BookMeshes;
	UPROPERTY(config)
	TArray<FSoftObjectPath> SwordMeshes;
	UPROPERTY(config)
	TArray<FSoftObjectPath> ShieldMeshes;

	TSharedPtr<FStreamableHandle> BodyMeshHandle;
	TSharedPtr<FStreamableHandle> HairMeshHandle;
	TSharedPtr<FStreamableHandle> HatMeshHandle;
	TSharedPtr<FStreamableHandle> WandMeshHandle;
	TSharedPtr<FStreamableHandle> BookMeshHandle;
	TSharedPtr<FStreamableHandle> SwordMeshHandle;
	TSharedPtr<FStreamableHandle> ShieldMeshHandle;

// Effect
public:
	FORCEINLINE UNiagaraComponent* GetSwordEffect() const { return SwordEffect; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Niagara, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraComponent> SwordEffect;

// Camera
public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

// Interaction Box
public:
	FORCEINLINE UBoxComponent* GetInteractionBox() const { return InteractionBox; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> InteractionBox;

// Input
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

// Ground Speed
public:
	FORCEINLINE float GetGroundSpeed() const { return GroundSpeed; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, Meta = (AllowPrivateAccess = true))
	float GroundSpeed;

// Attack
protected:
	virtual void AttackHitCheck() override;

// Skill
protected:
	virtual void SkillHitCheck() override;

// Take Exp
public:
	virtual void TakeExp(float ExpAmount);

// Take Damage
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// Dead
public:
	FORCEINLINE bool IsDead() const { return bIsDead; }

protected:
	virtual void SetDead();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetDead();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SetDead();

private:
	bool bIsDead = false;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DeadMontage;

// Respawn Player
protected:
	void RespawnPlayer();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> RespawnMontage;

// Stat
public:
	int32 GetLevel() const;
	void SetLevel(int32 InNewLevel);

protected:
	void ApplyStat(const FEQCharacterStat& BaseStat, const FEQCharacterStat& ModifierStat);

// UI Widget
protected:
	virtual void SetupCharacterWidget(UEQWidgetBase* InWidgetBase) override;

// User Name
protected:
	void UpdateUserName();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdateUserName(const FString& InUserName);

	UFUNCTION(Client, Reliable)
	void Client_UpdateUserName(const FString& InUserName);

// Component
public:
	FORCEINLINE UEQComponentMove* GetMoveComponent() const { return MoveComp; }
	FORCEINLINE UEQComponentStat* GetStatComponent() const { return StatComp; }
	FORCEINLINE UEQComponentAttack* GetAttackComponent() const { return AttackComp; }
	FORCEINLINE UEQComponentSkill* GetSkillComponent() const { return SkillComp; }
	FORCEINLINE UEQComponentWidget* GetUserNameComponent() const { return UserNameComp; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentMove> MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentAttack> AttackComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentSkill> SkillComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentStat> StatComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentInteraction> InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentInventory> InventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentMenuManager> MenuManagerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentQuest> QuestComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentWidget> UserNameComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UEQComponentWidget> HpBarComp;

	// 미니맵 로직 //
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> MinimapSpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneCaptureComponent2D> MinimapSceneCaptureComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInterface> MinimapMaterialInterface;

	UPROPERTY()
	TObjectPtr<UTextureRenderTarget2D> RenderTarget;
};
