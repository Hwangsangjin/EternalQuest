// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentBase.h"
#include "EQComponentSkill.generated.h"

class UInputAction;
class UAnimMontage;
class AEQProjectileBase;
class UNiagaraSystem;
class UStaticMesh;

UCLASS()
class ETERNALQUEST_API UEQComponentSkill : public UEQComponentBase
{
	GENERATED_BODY()

public:
	UEQComponentSkill();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Skill
public:
	FORCEINLINE bool IsSkill() const { return IsSkilling; }
	void SkillHitCheck();

private:
	bool IsSkilling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> FirstSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> SecondSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> ThirdSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> FourthSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> MageSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> WarriorSkillMontage;

// First Skill
protected:
	void FirstSkill();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_FirstSkill();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_FirstSkill();

// Mage First Skill
protected:
	void MageFirstSkill();
	void MageFirstSkillBegin();
	void MageFirstSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

// Warrior First Skill
protected:
	void WarriorFirstSkill();
	void WarriorFirstSkillBegin();
	void WarriorFirstSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

private:
	bool bHitDetected = false;
	FVector_NetQuantize TeleportPoint;

// Second Skill
protected:
	void SecondSkill();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SecondSkill();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_SecondSkill();

// Mage Second Skill
protected:
	void MageSecondSkill();
	void MageSecondSkillBegin();
	void MageSecondSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

// Warrior Second Skill
protected:
	void WarriorSecondSkill();
	void WarriorSecondSkillBegin();
	void WarriorSecondSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

// Third Skill
protected:
	void ThirdSkill();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ThirdSkill();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_ThirdSkill();

// Mage Third Skill
protected:
	void MageThirdSkill();
	void MageThirdSkillBegin();
	void MageThirdSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

// Warrior Third Skill
protected:
	void WarriorThirdSkill();
	void WarriorThirdSkillBegin();
	void WarriorThirdSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

// Fourth Skill
protected:
	void FourthSkill();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_FourthSkill();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_FourthSkill();

// Mage Fourth Skill
protected:
	void MageFourthSkill();
	void MageFourthSkillBegin();
	void MageFourthSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

// Warrior Fourth Skill
protected:
	void WarriorFourthSkill();
	void WarriorFourthSkillBegin();
	void WarriorFourthSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded);

// Area of Effect
public:
	void UpdatePreviewMesh();

private:
	bool bIsChanneling = false;
	bool bDoOnceMeshSet = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UStaticMeshComponent> PreviewMeshFactory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> PreviewMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMesh> PreviewMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UMaterialInterface> MaterialInterface;

	FTransform PreviewMeshTransform;
};
