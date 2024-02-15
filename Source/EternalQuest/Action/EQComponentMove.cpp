// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/EQComponentMove.h"

#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/EQPlayerController.h"

UEQComponentMove::UEQComponentMove()
{
	PrimaryComponentTick.bCanEverTick = false;

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
}

void UEQComponentMove::BeginPlay()
{
	Super::BeginPlay();
}

void UEQComponentMove::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	}
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
	
	if (Player->GetCameraBoom()->TargetArmLength >= 800 && LookAxis < 0) return;
	if (Player->GetCameraBoom()->TargetArmLength <= 200 && LookAxis > 0) return;

	if (LookAxis > 0)
		Player->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(Player->GetCameraBoom()->TargetArmLength, Player->GetCameraBoom()->TargetArmLength - 30.0f, GetWorld()->GetDeltaSeconds(), 150);
	else
		Player->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(Player->GetCameraBoom()->TargetArmLength, Player->GetCameraBoom()->TargetArmLength + 30.0f, GetWorld()->GetDeltaSeconds(), 150);
}

void UEQComponentMove::Jump(const FInputActionValue& Value)
{
	Player->Jump();
}

void UEQComponentMove::StopJumping(const FInputActionValue& Value)
{
	Player->StopJumping();
}

