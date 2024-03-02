// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentSkill.h"
#include "EnhancedInputComponent.h"
#include "Game/EQGameInstance.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQCharacterEnemy.h"
#include "Engine/DamageEvents.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/EQComponentAttack.h"
#include "Component/EQComponentAvoid.h"
#include "Component/EQComponentStat.h"
#include "Projectile/EQProjectileBase.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UEQComponentSkill::UEQComponentSkill()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> FirstSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_FirstSkill.IA_FirstSkill'"));
	if (FirstSkillActionRef.Succeeded())
	{
		FirstSkillAction = FirstSkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SecondSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_SecondSkill.IA_SecondSkill'"));
	if (SecondSkillActionRef.Succeeded())
	{
		SecondSkillAction = SecondSkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ThirdSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_ThirdSkill.IA_ThirdSkill'"));
	if (ThirdSkillActionRef.Succeeded())
	{
		ThirdSkillAction = ThirdSkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> FourthSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_FourthSkill.IA_FourthSkill'"));
	if (FourthSkillActionRef.Succeeded())
	{
		FourthSkillAction = FourthSkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> MageSkillMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_MageSkill.AM_MageSkill'"));
	if (MageSkillMontageRef.Succeeded())
	{
		MageSkillMontage = MageSkillMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> WarriorSkillMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_WarriorSkill.AM_WarriorSkill'"));
	if (WarriorSkillMontageRef.Succeeded())
	{
		WarriorSkillMontage = WarriorSkillMontageRef.Object;
	}
}

void UEQComponentSkill::BeginPlay()
{
	Super::BeginPlay();
}

void UEQComponentSkill::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(FirstSkillAction, ETriggerEvent::Triggered, this, &ThisClass::FirstSkill);
	EnhancedInputComponent->BindAction(SecondSkillAction, ETriggerEvent::Triggered, this, &ThisClass::SecondSkill);
	EnhancedInputComponent->BindAction(ThirdSkillAction, ETriggerEvent::Triggered, this, &ThisClass::ThirdSkill);
	EnhancedInputComponent->BindAction(FourthSkillAction, ETriggerEvent::Triggered, this, &ThisClass::FourthSkill);
}

void UEQComponentSkill::SkillHitCheck()
{
	TArray<FHitResult> OutHitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Skill), false, Player);

	constexpr float SkillRange = 150.0f;
	constexpr float SkillRadius = 150.0f;
	constexpr float SkillDamage = 2.0f;
	const FVector Start = Player->GetActorLocation();
	const FVector End = Start;

	const bool bHitDetected = GetWorld()->SweepMultiByChannel(OutHitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(SkillRadius), Params);
	if (bHitDetected)
	{
		FDamageEvent DamageEvent;
		for (const auto& OutHitResult : OutHitResults)
		{
			AEQCharacterEnemy* Enemy = Cast<AEQCharacterEnemy>(OutHitResult.GetActor());
			if (Enemy)
			{
				Enemy->TakeDamage(SkillDamage, DamageEvent, Player->GetController(), Player);
			}
		}
	}

//#if ENABLE_DRAW_DEBUG
//	const FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
//	const float CapsuleHalfHeight = SkillRange * 0.5f;
//	const FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;
//	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, SkillRadius, FRotationMatrix::MakeFromZ(Player->GetActorForwardVector()).ToQuat(), DrawColor, false, 1.0f);
//#endif
}

void UEQComponentSkill::FirstSkill()
{
	if (Player->GetAvoidComponent()->IsAvoid())
	{
		return;
	}

	if (Player->GetAttackComponent()->IsAttack())
	{
		return;
	}

	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (IsSkill())
	{
		return;
	}

	Server_FirstSkill();
}

bool UEQComponentSkill::Server_FirstSkill_Validate()
{
	return true;
}

void UEQComponentSkill::Server_FirstSkill_Implementation()
{
	NetMulticast_FirstSkill();
}

void UEQComponentSkill::NetMulticast_FirstSkill_Implementation()
{
	switch (Player->GetClassType())
	{
	case EClassType::ECT_Mage:
		MageFirstSkill();
		break;
	case EClassType::ECT_Paladin:
		break;
	case EClassType::ECT_Priest:
		break;
	case EClassType::ECT_Rogue:
		break;
	case EClassType::ECT_Warrior:
		WarriorFirstSkill();
		break;
	}
}

void UEQComponentSkill::MageFirstSkill()
{
}

void UEQComponentSkill::MageFirstSkillBegin()
{
}

void UEQComponentSkill::MageFirstSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
}

void UEQComponentSkill::WarriorFirstSkill()
{
	WarriorFirstSkillBegin();
}

void UEQComponentSkill::WarriorFirstSkillBegin()
{
	IsSkilling = true;
	Player->GetSwordEffect()->SetHiddenInGame(false);
	
	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(WarriorSkillMontage, PlayRate);
	AnimInstance->Montage_JumpToSection(TEXT("FirstSkill"), WarriorSkillMontage);

	Player->GetCharacterMovement()->GravityScale = 4.0f;

	constexpr float ForwardSpeed = 1500.0f;
	constexpr float UpSpeed = 1500.0f;
	const FVector LaunchVelocity = Player->GetActorForwardVector() * ForwardSpeed + Player->GetActorUpVector() * UpSpeed;
	Player->LaunchCharacter(FVector(0, 0, UpSpeed), false, false);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::WarriorFirstSkillEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, WarriorSkillMontage);
}

void UEQComponentSkill::WarriorFirstSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	TArray<FHitResult> OutHitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Skill), false, Player);

	constexpr float SkillRange = 200.0f;
	constexpr float SkillRadius = 150.0f;
	constexpr float SkillDamage = 20.0f;
	const FVector Start = Player->GetActorLocation();
	const FVector End = Start + Player->GetActorForwardVector() * SkillRange;

	const bool bHitDetected = GetWorld()->SweepMultiByChannel(OutHitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(SkillRadius), Params);
	if (bHitDetected)
	{
		FDamageEvent DamageEvent;
		for (const auto& OutHitResult : OutHitResults)
		{
			AEQCharacterEnemy* Enemy = Cast<AEQCharacterEnemy>(OutHitResult.GetActor());
			if (Enemy)
			{
				Enemy->TakeDamage(SkillDamage, DamageEvent, Player->GetController(), Player);
			}
		}
	}

//#if ENABLE_DRAW_DEBUG
//	const FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
//	const float CapsuleHalfHeight = SkillRange * 0.5f;
//	const FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;
//	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, SkillRadius, FRotationMatrix::MakeFromZ(Player->GetActorForwardVector()).ToQuat(), DrawColor, false, 1.0f);
//#endif

	Player->GetCharacterMovement()->GravityScale = 1.0f;
	Player->GetSwordEffect()->SetHiddenInGame(true);
	IsSkilling = false;
}

void UEQComponentSkill::SecondSkill()
{
	if (Player->GetAvoidComponent()->IsAvoid())
	{
		return;
	}

	if (Player->GetAttackComponent()->IsAttack())
	{
		return;
	}

	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (IsSkill())
	{
		return;
	}

	Server_SecondSkill();
}

bool UEQComponentSkill::Server_SecondSkill_Validate()
{
	return true;
}

void UEQComponentSkill::Server_SecondSkill_Implementation()
{
	NetMulticast_SecondSkill();
}

void UEQComponentSkill::NetMulticast_SecondSkill_Implementation()
{
	switch (Player->GetClassType())
	{
	case EClassType::ECT_Mage:
		MageSecondSkill();
		break;
	case EClassType::ECT_Paladin:
		break;
	case EClassType::ECT_Priest:
		break;
	case EClassType::ECT_Rogue:
		break;
	case EClassType::ECT_Warrior:
		WarriorSecondSkill();
		break;
	}
}

void UEQComponentSkill::MageSecondSkill()
{
}

void UEQComponentSkill::MageSecondSkillBegin()
{
}

void UEQComponentSkill::MageSecondSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
}

void UEQComponentSkill::WarriorSecondSkill()
{
	WarriorSecondSkillBegin();
}

void UEQComponentSkill::WarriorSecondSkillBegin()
{
	IsSkilling = true;
	Player->GetSwordEffect()->SetHiddenInGame(false);
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(WarriorSkillMontage, PlayRate);
	AnimInstance->Montage_JumpToSection(TEXT("SecondSkill"), WarriorSkillMontage);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::WarriorSecondSkillEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, WarriorSkillMontage);
}

void UEQComponentSkill::WarriorSecondSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	TArray<FHitResult> OutHitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Skill), false, Player);

	constexpr float AttackRange = 500.0f;
	constexpr float AttackRadius = 100.0f;
	constexpr float AttackDamage = 20.0f;
	const FVector Start = Player->GetActorLocation();
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

	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	Player->GetSwordEffect()->SetHiddenInGame(true);
	IsSkilling = false;
}

void UEQComponentSkill::ThirdSkill()
{
	if (Player->GetAvoidComponent()->IsAvoid())
	{
		return;
	}

	if (Player->GetAttackComponent()->IsAttack())
	{
		return;
	}

	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (IsSkill())
	{
		return;
	}

	Server_ThirdSkill();
}

bool UEQComponentSkill::Server_ThirdSkill_Validate()
{
	return true;
}

void UEQComponentSkill::Server_ThirdSkill_Implementation()
{
	NetMulticast_ThirdSkill();
}

void UEQComponentSkill::NetMulticast_ThirdSkill_Implementation()
{
	switch (Player->GetClassType())
	{
	case EClassType::ECT_Mage:
		MageThirdSkill();
		break;
	case EClassType::ECT_Paladin:
		break;
	case EClassType::ECT_Priest:
		break;
	case EClassType::ECT_Rogue:
		break;
	case EClassType::ECT_Warrior:
		WarriorThirdSkill();
		break;
	}
}

void UEQComponentSkill::MageThirdSkill()
{
}

void UEQComponentSkill::MageThirdSkillBegin()
{
}

void UEQComponentSkill::MageThirdSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
}

void UEQComponentSkill::WarriorThirdSkill()
{
	WarriorThirdSkillBegin();
}

void UEQComponentSkill::WarriorThirdSkillBegin()
{
	IsSkilling = true;
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(WarriorSkillMontage, PlayRate);
	AnimInstance->Montage_JumpToSection(TEXT("ThirdSkill"), WarriorSkillMontage);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::WarriorThirdSkillEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, WarriorSkillMontage);
}

void UEQComponentSkill::WarriorThirdSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	IsSkilling = false;
}

void UEQComponentSkill::FourthSkill()
{
	if (Player->GetAvoidComponent()->IsAvoid())
	{
		return;
	}

	if (Player->GetAttackComponent()->IsAttack())
	{
		return;
	}

	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (IsSkill())
	{
		return;
	}

	Server_FourthSkill();
}

bool UEQComponentSkill::Server_FourthSkill_Validate()
{
	return true;
}

void UEQComponentSkill::Server_FourthSkill_Implementation()
{
	NetMulticast_FourthSkill();
}

void UEQComponentSkill::NetMulticast_FourthSkill_Implementation()
{
	switch (Player->GetClassType())
	{
	case EClassType::ECT_Mage:
		MageFourthSkill();
		break;
	case EClassType::ECT_Paladin:
		break;
	case EClassType::ECT_Priest:
		break;
	case EClassType::ECT_Rogue:
		break;
	case EClassType::ECT_Warrior:
		WarriorFourthSkill();
		break;
	}
}

void UEQComponentSkill::MageFourthSkill()
{
}

void UEQComponentSkill::MageFourthSkillBegin()
{
}

void UEQComponentSkill::MageFourthSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
}

void UEQComponentSkill::WarriorFourthSkill()
{
	WarriorFourthSkillBegin();
}

void UEQComponentSkill::WarriorFourthSkillBegin()
{
	IsSkilling = true;

	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(WarriorSkillMontage, PlayRate);
	AnimInstance->Montage_JumpToSection(TEXT("FourthSkill"), WarriorSkillMontage);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::WarriorThirdSkillEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, WarriorSkillMontage);
}

void UEQComponentSkill::WarriorFourthSkillEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	IsSkilling = false;
}