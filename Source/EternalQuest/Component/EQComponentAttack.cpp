// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentAttack.h"
#include "EnhancedInputComponent.h"
#include "Animation/AnimMontage.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQCharacterComboAttackData.h"
#include "Character/EQCharacterEnemy.h"
#include "Component/EQComponentAvoid.h"
#include "Component/EQComponentStat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game/EQGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Projectile/EQProjectileBase.h"
#include "NiagaraComponent.h"

UEQComponentAttack::UEQComponentAttack()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Attack.IA_Attack'"));
	if (AttackActionRef.Succeeded())
	{
		AttackAction = AttackActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DefaultAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_DefaultAttack.AM_DefaultAttack'"));
	if (DefaultAttackMontageRef.Succeeded())
	{
		DefaultAttackMontage = DefaultAttackMontageRef.Object;
	}

	static ConstructorHelpers::FClassFinder<AEQProjectileBase> FireBallRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Effect/BP_FireBall.BP_FireBall_C'"));
	if (FireBallRef.Succeeded())
	{
		FireBall = FireBallRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_ComboAttack.AM_ComboAttack'"));
	if (ComboAttackMontageRef.Succeeded())
	{
		ComboAttackMontage = ComboAttackMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UEQCharacterComboAttackData> ComboAttackDataRef(TEXT("/Script/EternalQuest.EQCharacterComboAttackData'/Game/Blueprints/Data/DA_ComboAttack.DA_ComboAttack'"));
	if (ComboAttackDataRef.Succeeded())
	{
		ComboAttackData = ComboAttackDataRef.Object;
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
	if (Player->GetAvoidComponent()->IsAvoiding())
	{
		return;
	}

	Server_Attack();
}

void UEQComponentAttack::AttackHitCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, Player);

	/*const float AttackRange = Player->GetStatComponent()->GetTotalStat().AttackRange;
	const float AttackRadius = Player->GetStatComponent()->GetTotalStat().AttackRadius;
	const float AttackDamage = Player->GetStatComponent()->GetTotalStat().AttackDamage;*/
	const float AttackRange = 100.0f;
	const float AttackRadius = 50.0f;
	const float AttackDamage = 20.0f;
	const FVector Start = Player->GetActorLocation() + Player->GetActorForwardVector() * Player->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Player->GetActorForwardVector() * AttackRange;

	const bool bHitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (bHitDetected)
	{
		FDamageEvent DamageEvent;
		AEQCharacterEnemy* Enemy = Cast<AEQCharacterEnemy>(OutHitResult.GetActor());
		if (Enemy)
		{
			Enemy->TakeDamage(AttackDamage, DamageEvent, Player->GetController(), Player);
		}
	}

//#if ENABLE_DRAW_DEBUG
//	const FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
//	const float CapsuleHalfHeight = AttackRange * 0.5f;
//	const FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;
//	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Player->GetActorForwardVector()).ToQuat(), DrawColor, false, 5.0f);
//#endif
}

bool UEQComponentAttack::Server_Attack_Validate()
{
	return true;
}

void UEQComponentAttack::Server_Attack_Implementation()
{
	NetMulticast_Attack();
}

void UEQComponentAttack::NetMulticast_Attack_Implementation()
{
	switch (Player->GetClassType())
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

void UEQComponentAttack::DefaultAttack()
{
	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (bIsAttacking)
	{
		return;
	}

	DefaultAttackBegin();
}

void UEQComponentAttack::DefaultAttackBegin()
{
	bIsAttacking = true;
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	const FTransform Transform = Player->GetTransform();
	GetWorld()->SpawnActor<AEQProjectileBase>(FireBall, Transform);

	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(DefaultAttackMontage, PlayRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::DefaultAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, DefaultAttackMontage);
}

void UEQComponentAttack::DefaultAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	bIsAttacking = false;
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
	bIsAttacking = true;
	CurrentCombo = 1;
	Player->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	Player->GetSwordEffect()->SetHiddenInGame(false);

	//const float PlayRate = Player->GetStatComponent()->GetTotalStat().AttackSpeed;
	const float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboAttackMontage, PlayRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::ComboAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void UEQComponentAttack::ComboAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	bIsAttacking = false;
	Player->GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	Player->GetSwordEffect()->SetHiddenInGame(true);
}

void UEQComponentAttack::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboAttackData->GetEffectiveFrameCount().IsValidIndex(ComboIndex));

	//const float AttackSpeedRate = Player->GetStatComponent()->GetTotalStat().AttackSpeed;
	constexpr float PlayRate = 1.0f;
	const float EffectiveComboTime = (ComboAttackData->GetEffectiveFrameCount()[ComboIndex] / ComboAttackData->GetFrameRate()) / PlayRate;
	if (EffectiveComboTime > 0.0f)
	{
		GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ThisClass::ComboCheck, EffectiveComboTime, false);
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
		AnimInstance->Montage_JumpToSection(NextSection, ComboAttackMontage);

		SetComboCheckTimer();

		bHasNextComboCommand = false;
	}
}
