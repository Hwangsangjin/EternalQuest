// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentAvoid.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Component/EQComponentAttack.h"
#include "Component/EQComponentMove.h"
#include "GameFramework/CharacterMovementComponent.h"

UEQComponentAvoid::UEQComponentAvoid()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> AvoidActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Avoid.IA_Avoid'"));
	if (AvoidActionRef.Object)
	{
		AvoidAction = AvoidActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RollMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_Roll.AM_Roll'"));
	if (RollMontageRef.Object)
	{
		RollMontage = RollMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> TeleportMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_Teleport.AM_Teleport'"));
	if (TeleportMontageRef.Object)
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

//#if ENABLE_DRAW_DEBUG
//	const FColor DrawColor = bHitDetected ? FColor::Green : FColor::Red;
//	DrawDebugLine(GetWorld(), Start, End, DrawColor, false, 5.0f);
//#endif
}

void UEQComponentAvoid::Avoid(const FInputActionValue& Value)
{
	if (IsAvoiding())
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
		Roll();
		break;
	}
}

void UEQComponentAvoid::Roll()
{
	if (Player->GetCharacterMovement()->GetCurrentAcceleration().IsZero())
	{
		return;
	}

	RollBegin();
}

void UEQComponentAvoid::RollBegin()
{
	bIsAvoiding = true;

	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(RollMontage, PlayRate);

	if (Player->GetMoveComponent()->IsSprinting())
	{
		AnimInstance->Montage_JumpToSection(TEXT("Sprint"), RollMontage);
	}
	else
	{
		AnimInstance->Montage_JumpToSection(TEXT("Default"), RollMontage);
	}

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::RollEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, RollMontage);
}

void UEQComponentAvoid::RollEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	bIsAvoiding = false;
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
	bIsAvoiding = false;

	if (bHitDetected)
	{
		Player->AddActorLocalOffset(TeleportPoint, true);
	}
	else
	{
		TeleportPoint = FVector_NetQuantize(1000, 0, 50);
		Player->AddActorLocalOffset(TeleportPoint, true);
	}
}
