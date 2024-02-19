// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentMove.h"

#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/EQPlayerController.h"

UEQComponentMove::UEQComponentMove()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Jump.IA_Jump'"));
	if (InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Move.IA_Move'"));
	if (InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionTurnRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Turn.IA_Turn'"));
	if (InputActionTurnRef.Object)
	{
		TurnAction = InputActionTurnRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Look.IA_Look'"));
	if (InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSprintRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Sprint.IA_Sprint'"));
	if (InputActionSprintRef.Object)
	{
		SprintAction = InputActionSprintRef.Object;
	}
}

void UEQComponentMove::BeginPlay()
{
	Super::BeginPlay();
}

void UEQComponentMove::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &UEQComponentMove::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UEQComponentMove::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UEQComponentMove::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &UEQComponentMove::Turn);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UEQComponentMove::Look);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::Sprint);
	}
}

void UEQComponentMove::Jump(const FInputActionValue& Value)
{
	Player->Jump();
}

void UEQComponentMove::StopJumping(const FInputActionValue& Value)
{
	Player->StopJumping();
}

void UEQComponentMove::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = EQPlayerController->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	Player->AddMovementInput(ForwardDirection, MovementVector.Y);
	Player->AddMovementInput(RightDirection, MovementVector.X);
}

void UEQComponentMove::Turn(const FInputActionValue& Value)
{
	const FVector2D TurnAxisVector = Value.Get<FVector2D>();

	Player->AddControllerYawInput(TurnAxisVector.X);
	Player->AddControllerPitchInput(TurnAxisVector.Y);
}

void UEQComponentMove::Look(const FInputActionValue& Value)
{
	const float LookAxis = Value.Get<float>();
	
	constexpr float MinLength = 200.0f;
	constexpr float MaxLength = 800.0f;
	if (Player->GetCameraBoom()->TargetArmLength <= MinLength && LookAxis > 0) return;
	if (Player->GetCameraBoom()->TargetArmLength >= MaxLength && LookAxis < 0) return;

	if (LookAxis > 0)
	{
		Player->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(Player->GetCameraBoom()->TargetArmLength, Player->GetCameraBoom()->TargetArmLength - 30.0f, GetWorld()->GetDeltaSeconds(), 150);
	}
	else
	{
		Player->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(Player->GetCameraBoom()->TargetArmLength, Player->GetCameraBoom()->TargetArmLength + 30.0f, GetWorld()->GetDeltaSeconds(), 150);
	}
}

void UEQComponentMove::Sprint(const FInputActionValue& Value)
{
	const bool bIsSprinting = Value.Get<bool>();
	if (bIsSprinting)
	{
		constexpr float MaxSpeed = 600.0f;
		Player->GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	}
	else
	{
		constexpr float DefaultSpeed = 450.0f;
		Player->GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	}
}
