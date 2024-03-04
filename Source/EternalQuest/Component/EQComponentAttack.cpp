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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> MageAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_MageAttack.AM_MageAttack'"));
	if (MageAttackMontageRef.Succeeded())
	{
		MageAttackMontage = MageAttackMontageRef.Object;
	}

	static ConstructorHelpers::FClassFinder<AEQProjectileBase> FireBallRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Effect/BP_FireBall.BP_FireBall_C'"));
	if (FireBallRef.Succeeded())
	{
		FireBall = FireBallRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> WarriorAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_WarriorAttack.AM_WarriorAttack'"));
	if (WarriorAttackMontageRef.Succeeded())
	{
		WarriorAttackMontage = WarriorAttackMontageRef.Object;
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
	if (Player->GetAvoidComponent()->IsAvoid())
	{
		return;
	}

	Server_Attack();
}

void UEQComponentAttack::AttackHitCheck()
{
	TArray<FHitResult> OutHitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Skill), false, Player);

	/*const float AttackRange = Player->GetStatComponent()->GetTotalStat().AttackRange;
	const float AttackRadius = Player->GetStatComponent()->GetTotalStat().AttackRadius;
	const float AttackDamage = Player->GetStatComponent()->GetTotalStat().AttackDamage;*/
	constexpr float AttackRange = 100.0f;
	constexpr float AttackRadius = 50.0f;
	constexpr float AttackDamage = 10.0f;
	const FVector Start = Player->GetActorLocation() + Player->GetActorForwardVector() * Player->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Player->GetActorForwardVector() * AttackRange;

	const bool bHitDetected = GetWorld()->SweepMultiByChannel(OutHitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (bHitDetected)
	{
		FDamageEvent DamageEvent;
		for (const auto& OutHitResult : OutHitResults)
		{
			AEQCharacterEnemy* Enemy = Cast<AEQCharacterEnemy>(OutHitResult.GetActor());
			if (Enemy)
			{
				Enemy->TakeDamage(AttackDamage, DamageEvent, Player->GetController(), Player);
			}
		}
	}

//#if ENABLE_DRAW_DEBUG
//	const FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
//	const float CapsuleHalfHeight = AttackRange * 0.5f;
//	const FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;
//	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Player->GetActorForwardVector()).ToQuat(), DrawColor, false, 1.0f);
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
		MageAttack();
		break;
	case EClassType::ECT_Paladin:
		break;
	case EClassType::ECT_Priest:
		break;
	case EClassType::ECT_Rogue:
		break;
	case EClassType::ECT_Warrior:
		WarriorAttack();
		break;
	}
}

void UEQComponentAttack::MageAttack()
{
	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (bIsAttacking)
	{
		return;
	}

	MageAttackBegin();
}

void UEQComponentAttack::MageAttackBegin()
{
	bIsAttacking = true;
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	const FTransform Transform = Player->GetTransform();
	GetWorld()->SpawnActor<AEQProjectileBase>(FireBall, Transform);

	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(MageAttackMontage, PlayRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::MageAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, MageAttackMontage);
}

void UEQComponentAttack::MageAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	bIsAttacking = false;
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UEQComponentAttack::WarriorAttack()
{
	if (CurrentCombo == 0)
	{
		WarriorAttackBegin();
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

void UEQComponentAttack::WarriorAttackBegin()
{
	bIsAttacking = true;
	Player->GetSwordEffect()->SetHiddenInGame(false);
	Player->GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	CurrentCombo = 1;

	//const float PlayRate = Player->GetStatComponent()->GetTotalStat().AttackSpeed;
	const float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(WarriorAttackMontage, PlayRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::WarriorAttackEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, WarriorAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void UEQComponentAttack::WarriorAttackEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	Player->GetCharacterMovement()->MaxWalkSpeed = 450.0f;
	Player->GetSwordEffect()->SetHiddenInGame(true);
	bIsAttacking = false;
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
		AnimInstance->Montage_JumpToSection(NextSection, WarriorAttackMontage);

		SetComboCheckTimer();

		bHasNextComboCommand = false;
	}
}
