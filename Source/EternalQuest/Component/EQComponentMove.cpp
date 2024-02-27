// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentMove.h"

#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/EQPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Widget/EQWidgetChatMessage.h"
#include "Widget/EQWidgetChattingSystem.h"
#include "Widget/EQWidgetMainUI.h"
#include "Component/EQComponentAttack.h"

UEQComponentMove::UEQComponentMove()
{
	PrimaryComponentTick.bCanEverTick = true;

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

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionEnterRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Enter.IA_Enter'"));
	if (InputActionEnterRef.Object)
	{
		EnterAction = InputActionEnterRef.Object;
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Turn);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		EnhancedInputComponent->BindAction(AvoidAction, ETriggerEvent::Triggered, this, &ThisClass::Avoid);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::StopSprinting);
		EnhancedInputComponent->BindAction(EnterAction, ETriggerEvent::Completed, this, &ThisClass::Enter);
	}
}

void UEQComponentMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsSprinting)
	{
		constexpr float DefaultFieldOfView = 90.0f;
		constexpr int32 DefaultInterpSpeed = 5;
		CurrentFieldOfView = FMath::FInterpTo(CurrentFieldOfView, DefaultFieldOfView, DeltaTime, DefaultInterpSpeed);
		Player->GetFollowCamera()->FieldOfView = CurrentFieldOfView;
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
	if (Player->GetCameraBoom()->TargetArmLength <= MinLength && LookAxis > 0)
	{
		return;
	}

	constexpr float MaxLength = 800.0f;
	if (Player->GetCameraBoom()->TargetArmLength >= MaxLength && LookAxis < 0)
	{
		return;
	}

	const float CurrentTargetArmLength = Player->GetCameraBoom()->TargetArmLength;
	const float MinTargetArmLength = CurrentTargetArmLength - 30.0f;
	const float MaxTargetArmLength = CurrentTargetArmLength + 30.0f;
	constexpr int32 InterpSpeed = 150;

	if (LookAxis > 0)
	{
		Player->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, MinTargetArmLength, GetWorld()->GetDeltaSeconds(), InterpSpeed);
	}
	else
	{
		Player->GetCameraBoom()->TargetArmLength = FMath::FInterpTo(CurrentTargetArmLength, MaxTargetArmLength, GetWorld()->GetDeltaSeconds(), InterpSpeed);
	}
}

void UEQComponentMove::Avoid(const FInputActionValue& Value)
{
	if (IsAvoiding())
	{
		return;
	}

	Server_Avoid();
}

bool UEQComponentMove::Server_Avoid_Validate()
{
	return true;
}

void UEQComponentMove::Server_Avoid_Implementation()
{
	NetMulticast_Avoid();
}

void UEQComponentMove::NetMulticast_Avoid_Implementation()
{
	switch (Player->GetClassType())
	{
	case EClassType::ECT_Mage:
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

void UEQComponentMove::Roll()
{
	if (Player->GetCharacterMovement()->GetCurrentAcceleration().IsZero())
	{
		return;
	}

	RollBegin();
}

void UEQComponentMove::RollBegin()
{
	bIsAvoiding = true;

	const float AvoidSpeedRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(RollMontage, AvoidSpeedRate);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ThisClass::RollEnd);
	AnimInstance->Montage_SetEndDelegate(EndDelegate, RollMontage);
}

void UEQComponentMove::RollEnd(UAnimMontage* TargetMontage, bool bIsProperlyEnded)
{
	bIsAvoiding = false;
}

void UEQComponentMove::Sprint(const FInputActionValue& Value)
{
	if (Player->GetCharacterMovement()->GetCurrentAcceleration().IsZero())
	{
		return;
	}

	if (Player->GetAttackComponent()->IsAttack())
	{
		return;
	}

	bIsSprinting = Value.Get<bool>();
	if (bIsSprinting)
	{
		constexpr float SprintSpeed = 600.0f;
		Player->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

		if (GetWorld()->GetGameInstance()->GetTimerManager().IsTimerActive(SprintTimerHandle))
		{
			GetWorld()->GetGameInstance()->GetTimerManager().ClearTimer(SprintTimerHandle);
		}

		constexpr float SprintFieldOfView = 70.0f;
		constexpr int32 SprintInterpSpeed = 1;
		CurrentFieldOfView = FMath::FInterpTo(CurrentFieldOfView, SprintFieldOfView, GetWorld()->GetDeltaSeconds(), SprintInterpSpeed);
		Player->GetFollowCamera()->FieldOfView = CurrentFieldOfView;
	}
}

void UEQComponentMove::StopSprinting(const FInputActionValue& Value)
{
	bIsSprinting = Value.Get<bool>();
	if (!bIsSprinting)
	{
		constexpr float DefaultSpeed = 450.0f;
		Player->GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
		
		/*constexpr float DefaultFieldOfView = 90.0f;
		if (CurrentFieldOfView >= DefaultFieldOfView - KINDA_SMALL_NUMBER)
		{
			GetWorld()->GetGameInstance()->GetTimerManager().ClearTimer(SprintTimerHandle);
		}

		GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(SprintTimerHandle, FTimerDelegate::CreateLambda([&]
			{
				constexpr int32 DefaultInterpSpeed = 5;
				CurrentFieldOfView = FMath::FInterpTo(CurrentFieldOfView, DefaultFieldOfView, GetWorld()->GetDeltaSeconds(), DefaultInterpSpeed);
				Player->GetFollowCamera()->FieldOfView = CurrentFieldOfView;
			}), GetWorld()->GetDeltaSeconds(), true);*/
	}
}

void UEQComponentMove::Enter(const FInputActionValue& Value)
{
	auto MyEQChatWidget = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetChattingSystem;
	if (MyEQChatWidget->EditText_ChatInput->GetText().IsEmpty())
	{
		MyEQChatWidget->EditText_ChatInput->SetKeyboardFocus();
	}
}

void UEQComponentMove::ServerRPC_SendChat_Implementation(const FText& InText, const FText& InPlayerName)
{
	// for (auto e : GetWorld()->GetGameState()->PlayerArray)
	// {
	// 	auto Cast_e = Cast<AEQPlayerController>(e->GetPlayerController());
	// 	Cast_e->GetCharacter()->FindComponentByClass<UEQComponentMove>()->ClientRPC_SendChat(InText, InPlayerName);
	// }

	for (auto e : TActorRange<AEQPlayerController>(GetWorld()))
	{
		e->GetCharacter()->FindComponentByClass<UEQComponentMove>()->ClientRPC_SendChat(InText, InPlayerName);
		// ClientRPC_SendChat(InText, InPlayerName);
	}
}
void UEQComponentMove::ClientRPC_SendChat_Implementation(const FText& InText, const FText& InPlayerName)
{
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetChattingSystem->UpdateChat(InText, InPlayerName);
}
