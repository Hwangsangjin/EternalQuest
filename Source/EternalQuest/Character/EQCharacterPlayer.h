// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EQCharacterBase.h"
#include "EQCharacterPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInputComponent;
class UBoxComponent;
class UEQComponentMove;

DECLARE_MULTICAST_DELEGATE_OneParam(FInputSignature, UInputComponent*)

UENUM(BlueprintType)
enum class EJobType : uint8
{
	EJT_Mage,
	EJT_Knight,
	EJT_Priest,
	EJT_Rogue,
	EJT_Warrior,

	MAX
};

UCLASS()
class ETERNALQUEST_API AEQCharacterPlayer : public AEQCharacterBase
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
	FORCEINLINE UBoxComponent* GetInteractionBox() const { return InteractionBox; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> InteractionBox;

// Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

// Component
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEQComponentMove> MoveComp;

// Job Type
public:
	void SetJobType(EJobType InJobType);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Job, Meta = (AllowPrivateAccess = true))
	EJobType JobType;
};
