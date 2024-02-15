// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/EQComponentAttack.h"
#include "EnhancedInputComponent.h"
#include "Animation/AnimMontage.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQCharacterComboAttackData.h"
#include "Action/EQComponentMove.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game/EQGameInstance.h"

UEQComponentAttack::UEQComponentAttack()
{
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Attack.IA_Attack'"));
	if (InputActionAttackRef.Object)
	{
		AttackAction = InputActionAttackRef.Object;
	}
}

void UEQComponentAttack::BeginPlay()
{
	Super::BeginPlay();
}

void UEQComponentAttack::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ThisClass::Attack);
}

void UEQComponentAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQComponentAttack::Attack()
{
	UEQGameInstance* GameInstance = Cast<UEQGameInstance>(Player->GetGameInstance());
	if (GameInstance->GetClassType() == EClassType::ECT_Mage)
	{
		DefaultAttackProcess();
	}
	else if (GameInstance->GetClassType() == EClassType::ECT_Warrior)
	{
		ComboAttackCommand();
	}
}

void UEQComponentAttack::DefaultAttackProcess()
{
	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (bIsDefaultAttacking)
	{
		return;
	}

	DefaultAttackBegin();
}

void UEQComponentAttack::DefaultAttackBegin()
{
	bIsDefaultAttacking = true;
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(AttackMontage, AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::DefaultAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
}

void UEQComponentAttack::DefaultAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	bIsDefaultAttacking = false;
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UEQComponentAttack::ComboAttackCommand()
{
	if (CurrentCombo == 0)
	{
		ComboAttackBegin();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		bHasNextComboCommand = false;
	}
	else
	{
		bHasNextComboCommand = true;
	}
}

void UEQComponentAttack::ComboAttackBegin()
{
	CurrentCombo = 1;
	Player->GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	const float AttackSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(AttackMontage, AttackSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::ComboAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void UEQComponentAttack::ComboAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	Player->GetCharacterMovement()->MaxWalkSpeed = 450.0f;
}

void UEQComponentAttack::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboAttackData->GetEffectiveFrameCount().IsValidIndex(ComboIndex));

	const float AttackSpeedRate = 1.0f;
	const float EffectiveComboTime = (ComboAttackData->GetEffectiveFrameCount()[ComboIndex] / ComboAttackData->GetFrameRate()) / AttackSpeedRate;
	if (EffectiveComboTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ThisClass::ComboCheck, EffectiveComboTime, false);
	}
}

void UEQComponentAttack::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (bHasNextComboCommand)
	{
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboAttackData->GetMaxComboCount());
		const FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboAttackData->GetMontageSectionNamePrefix(), CurrentCombo);

		UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
		AnimInstance->Montage_JumpToSection(NextSection, AttackMontage);

		SetComboCheckTimer();

		bHasNextComboCommand = false;
	}
}
