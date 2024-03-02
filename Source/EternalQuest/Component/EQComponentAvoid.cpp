// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentAvoid.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Character/EQCharacterEnemy.h"
#include "Engine/DamageEvents.h"
#include "Component/EQComponentAttack.h"
#include "Component/EQComponentMove.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"

UEQComponentAvoid::UEQComponentAvoid()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> AvoidActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Avoid.IA_Avoid'"));
	if (AvoidActionRef.Succeeded())
	{
		AvoidAction = AvoidActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SlideMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_Slide.AM_Slide'"));
	if (SlideMontageRef.Succeeded())
	{
		SlideMontage = SlideMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> TeleportMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_Teleport.AM_Teleport'"));
	if (TeleportMontageRef.Succeeded())
	{
		TeleportMontage = TeleportMontageRef.Object;
	}
}

void UEQComponentAvoid::BeginPlay()
{
	Super::BeginPlay();
}

void UEQComponentAvoid::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(AvoidAction, ETriggerEvent::Started, this, &ThisClass::Avoid);
	}
}

void UEQComponentAvoid::AvoidableCheck()
{
	FHitResult OutHitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Avoid), false, Player);

	constexpr float TraceRange = 1000.0f;
	const FVector Start = Player->GetActorLocation();
	const FVector Current = Player->GetActorLocation();
	const FVector End = Current + Player->GetActorForwardVector() * TraceRange;

	bHitDetected = GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, Params);
	if (bHitDetected)
	{
		constexpr float TraceOffset = 50.0f;
		TeleportPoint = OutHitResult.ImpactPoint - (Current + Player->GetActorForwardVector() * TraceOffset);
	}

#if ENABLE_DRAW_DEBUG
	const FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), Start, End, DrawColor, false, 5.0f);
#endif
}

void UEQComponentAvoid::Avoid(const FInputActionValue& Value)
{
	if (IsAvoid())
	{
		return;
	}

	if (Player->GetAttackComponent()->IsAttack())
	{
		return;
	}

	Server_Avoid();
}

bool UEQComponentAvoid::Server_Avoid_Validate()
{
	return true;
}

void UEQComponentAvoid::Server_Avoid_Implementation()
{
	NetMulticast_Avoid();
}

void UEQComponentAvoid::NetMulticast_Avoid_Implementation()
{
	switch (Player->GetClassType())
	{
	case EClassType::ECT_Mage:
		Teleport();
		break;
	case EClassType::ECT_Paladin:
		break;
	case EClassType::ECT_Priest:
		break;
	case EClassType::ECT_Rogue:
		break;
	case EClassType::ECT_Warrior:
		Slide();
		break;
	}
}

void UEQComponentAvoid::Teleport()
{
	TeleportBegin();
}

void UEQComponentAvoid::TeleportBegin()
{
	bIsAvoiding = true;

	constexpr float PlayRate = 2.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(TeleportMontage, PlayRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::TeleportEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, TeleportMontage);
}

void UEQComponentAvoid::TeleportEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	if (bHitDetected)
	{
		Player->AddActorLocalOffset(TeleportPoint, true);
	}
	else
	{
		TeleportPoint = FVector_NetQuantize(1000, 0, 50);
		Player->AddActorLocalOffset(TeleportPoint, true);
	}

	bIsAvoiding = false;
}

void UEQComponentAvoid::Slide()
{
	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	SlideBegin();
}

void UEQComponentAvoid::SlideBegin()
{
	bIsAvoiding = true;
	Player->GetSwordEffect()->SetHiddenInGame(false);

	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(SlideMontage, PlayRate);

	FVector LaunchDirection = Player->GetActorForwardVector();
	LaunchDirection.Z = 0.0f;
	LaunchDirection.Normalize();
	constexpr float ForwardSpeed = 2500.0f;
	const FVector LaunchVelocity = LaunchDirection * ForwardSpeed;
	Player->LaunchCharacter(LaunchVelocity, false, false);

	TArray<FHitResult> OutHitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Skill), false, Player);

	constexpr float AttackRange = 250.0f;
	constexpr float AttackRadius = 50.0f;
	constexpr float AttackDamage = 10.0f;
	const FVector Start = Player->GetActorLocation();
	const FVector End = Start + Player->GetActorForwardVector() * AttackRange;

	bHitDetected = GetWorld()->SweepMultiByChannel(OutHitResults, Start, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius), Params);
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

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::SlideEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, SlideMontage);
}

void UEQComponentAvoid::SlideEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	Player->GetSwordEffect()->SetHiddenInGame(true);
	bIsAvoiding = false;
}
