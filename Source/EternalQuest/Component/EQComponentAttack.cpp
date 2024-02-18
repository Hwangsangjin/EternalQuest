// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentAttack.h"
#include "EnhancedInputComponent.h"
#include "Animation/AnimMontage.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQCharacterComboAttackData.h"
#include "Component/EQComponentMove.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game/EQGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"

UEQComponentAttack::UEQComponentAttack()
{
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

void UEQComponentAttack::Attack()
{
	UEQGameInstance* GameInstance = Cast<UEQGameInstance>(Player->GetGameInstance());
	EClassType ClassType = GameInstance->GetClassType();
	switch (ClassType)
	{
	case EClassType::ECT_Mage:
		DefaultAttack();
		break;
	case EClassType::ECT_Paladin:
		break;
	case EClassType::ECT_Priest:
		break;
	case EClassType::ECT_Rogue:
		break;
	case EClassType::ECT_Warrior:
		ComboAttack();
		break;
	}
}

void UEQComponentAttack::HitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, Player);

	const float AttackRange = 100.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 30.0f;
	const FVector Start = Player->GetActorLocation() + Player->GetActorForwardVector() * Player->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Player->GetActorForwardVector() * AttackRange;

	const bool bHitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (bHitDetected)
	{
		FDamageEvent DamageEvent;
		OutHitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, Player->GetController(), Player);
	}

#if ENABLE_DRAW_DEBUG
	const FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	const float CapsuleHalfHeight = AttackRange * 0.5f;
	const FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;
	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Player->GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
#endif
}

void UEQComponentAttack::DefaultAttack()
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

void UEQComponentAttack::ComboAttack()
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
