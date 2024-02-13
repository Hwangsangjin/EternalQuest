// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Action/EQComponentMove.h"
#include "Action/EQComponentInteraction.h"
#include "Kismet/GameplayStatics.h"

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
}

void AEQCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
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

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}
}

void AEQCharacterPlayer::OnRep_Owner()
{
	Super::OnRep_Owner();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}
}