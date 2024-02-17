// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Component/EQComponentMove.h"
#include "Component/EQComponentInteraction.h"
#include "Component/EQComponentInventory.h"
#include "Component/EQComponentMenuManager.h"
#include "Component/EQComponentAttack.h"

AEQCharacterPlayer::AEQCharacterPlayer()
{
	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT(""));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/Blueprints/Animation/ABP_CharacterPlayer.ABP_CharacterPlayer_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Interaction Box
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	InteractionBox->SetBoxExtent(FVector(50));
	InteractionBox->SetRelativeLocation(FVector(120, 0, -50));

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/Input/IMC_Default.IMC_Default'"));
	if (InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	// Component
	MoveComp = CreateDefaultSubobject<UEQComponentMove>(TEXT("Move Component"));
	InteractionComp = CreateDefaultSubobject<UEQComponentInteraction>(TEXT("Interaction Component"));
	InventoryComp = CreateDefaultSubobject<UEQComponentInventory>(TEXT("Inventory Component"));
	MenuManagerComp = CreateDefaultSubobject<UEQComponentMenuManager>(TEXT("MenuManager Component"));
	AttackComp = CreateDefaultSubobject<UEQComponentAttack>(TEXT("Attack Component"));
}

void AEQCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AEQCharacterPlayer::AttackHitCheck()
{
	AttackComp->HitCheck();
}

float AEQCharacterPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetDead();

	return DamageAmount;
}

void AEQCharacterPlayer::SetDead()
{
	/*GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
	SetActorEnableCollision(false);*/
	Jump();
}

void AEQCharacterPlayer::PlayDeadAnimation()
{
	UAnimInstance* Animinstance = GetMesh()->GetAnimInstance();
	Animinstance->StopAllMontages(0.0f);
	Animinstance->Montage_Play(DeadMontage, 1.0f);
}

void AEQCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputSignature.Broadcast(PlayerInputComponent);
}

void AEQCharacterPlayer::Jump()
{
	Super::Jump();
}

void AEQCharacterPlayer::StopJumping()
{
	Super::StopJumping();
}

void AEQCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AEQCharacterPlayer::OnRep_Owner()
{
	Super::OnRep_Owner();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}