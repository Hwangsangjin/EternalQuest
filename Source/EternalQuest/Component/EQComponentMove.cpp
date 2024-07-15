// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentMove.h"

#include "EngineUtils.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Component/EQComponentAttack.h"
#include "Component/EQComponentSkill.h"
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

UEQComponentMove::UEQComponentMove()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Jump.IA_Jump'"));
	if (JumpActionRef.Succeeded())
	{
		JumpAction = JumpActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Move.IA_Move'"));
	if (MoveActionRef.Succeeded())
	{
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TurnActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Turn.IA_Turn'"));
	if (TurnActionRef.Succeeded())
	{
		TurnAction = TurnActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Look.IA_Look'"));
	if (LookActionRef.Succeeded())
	{
		LookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SprintActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Sprint.IA_Sprint'"));
	if (SprintActionRef.Succeeded())
	{
		SprintAction = SprintActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> EnterActionrRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Input/Actions/IA_Enter.IA_Enter'"));
	if (EnterActionrRef.Succeeded())
	{
		EnterAction = EnterActionrRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ParkourMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Assets/StylizedCharactersPack/Common/Animation/Montage/AM_Parkour.AM_Parkour'"));
	if (ParkourMontageRef.Succeeded())
	{
		ParkourMontage = ParkourMontageRef.Object;
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
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ThisClass::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::StopSprinting);
		EnhancedInputComponent->BindAction(EnterAction, ETriggerEvent::Completed, this, &ThisClass::Enter);
	}
}

void UEQComponentMove::Jump(const FInputActionValue& Value)
{
	if (Player->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (Player->GetSkillComponent()->IsSkill())
	{
		return;
	}

	switch (Player->GetClassType())
	{
	case EClassType::ECT_Mage:
		Player->Jump();
		break;
	case EClassType::ECT_Paladin:
		break;
	case EClassType::ECT_Priest:
		break;
	case EClassType::ECT_Rogue:
		break;
	case EClassType::ECT_Warrior:
		if (IsSprinting() && !Player->GetCharacterMovement()->GetCurrentAcceleration().IsZero())
		{
			Server_Jump();
			Player->Jump();
			break;
		}
		else
		{
			Player->Jump();
			break;
		}
	}
}

bool UEQComponentMove::Server_Jump_Validate()
{
	return true;
}

void UEQComponentMove::Server_Jump_Implementation()
{
	NetMulticast_Jump();
}

void UEQComponentMove::NetMulticast_Jump_Implementation()
{
	constexpr float PlayRate = 1.0f;
	UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ParkourMontage, PlayRate);
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

void UEQComponentMove::Sprint(const FInputActionValue& Value)
{
	if (Player->IsLocallyControlled())
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
	else
	{
		Server_Sprint(Value);
	}
}

bool UEQComponentMove::Server_Sprint_Validate(const FInputActionValue& Value)
{
	return true;
}

void UEQComponentMove::Server_Sprint_Implementation(const FInputActionValue& Value)
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

	Client_Sprint(Value);
}

void UEQComponentMove::Client_Sprint_Implementation(const FInputActionValue& Value)
{
}

void UEQComponentMove::StopSprinting(const FInputActionValue& Value)
{
	Server_StopSprinting(Value);
}

bool UEQComponentMove::Server_StopSprinting_Validate(const FInputActionValue& Value)
{
	return true;
}

void UEQComponentMove::Server_StopSprinting_Implementation(const FInputActionValue& Value)
{
	NetMulticast_StopSprinting(Value);
}

void UEQComponentMove::NetMulticast_StopSprinting_Implementation(const FInputActionValue& Value)
{
	if (Player->IsLocallyControlled())
	{
		bIsSprinting = Value.Get<bool>();
		if (!bIsSprinting)
		{
			constexpr float DefaultSpeed = 450.0f;
			Player->GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;

			constexpr float DefaultFieldOfView = 90.0f;
			if (CurrentFieldOfView >= DefaultFieldOfView - KINDA_SMALL_NUMBER)
			{
				GetWorld()->GetGameInstance()->GetTimerManager().ClearTimer(SprintTimerHandle);
			}

			GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(SprintTimerHandle, this, &ThisClass::ResetFieldOfView, GetWorld()->GetDeltaSeconds(), true);
		}
	}
}

void UEQComponentMove::ResetFieldOfView()
{
	constexpr int32 DefaultInterpSpeed = 5;
	constexpr float DefaultFieldOfView = 90.0f;
	CurrentFieldOfView = FMath::FInterpTo(CurrentFieldOfView, DefaultFieldOfView, GetWorld()->GetDeltaSeconds(), DefaultInterpSpeed);
	Player->GetFollowCamera()->FieldOfView = CurrentFieldOfView;
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
