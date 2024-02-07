// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/EQComponentInteraction.h"

#include "EnhancedInputComponent.h"
#include "Character/EQCharacterNeutralPlayer.h"
#include "Character/EQCharacterNonPlayer.h"
#include "Character/EQCharacterPlayer.h"
#include "Components/BoxComponent.h"

UEQComponentInteraction::UEQComponentInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionActionRef(TEXT("/Game/LDJ/Inputs/IA_Interaction.IA_Interaction"));
	if (InteractionActionRef.Object)
	{
		InteractionAction = InteractionActionRef.Object;
	}

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));

	InteractionBox->SetBoxExtent(FVector(50));
	InteractionBox->SetRelativeLocation(FVector(120,0,0));
}

void UEQComponentInteraction::BeginPlay()
{
	Super::BeginPlay();
}

void UEQComponentInteraction::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto HitResult = GetWorld()->LineTraceSingleByChannel(HitInfo, Player->GetActorLocation(), Player->GetActorLocation() + Player->GetActorForwardVector() * 150, ECC_Visibility, Params);
	
	DrawDebugLine(GetWorld(), Player->GetActorLocation(), Player->GetActorLocation() + Player->GetActorForwardVector() * 150, FColor::Red);
	
	if (HitResult)
	{
		auto temp = Cast<AEQCharacterNeutralPlayer>(HitInfo.GetActor());
		if (temp)
		{
		}
	}
}

void UEQComponentInteraction::InitializeComponent()
{
	Super::InitializeComponent();
	Params.AddIgnoredActor(Player);
}

void UEQComponentInteraction::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &UEQComponentInteraction::Interaction);
	}
}

void UEQComponentInteraction::Interaction()
{
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, TEXT("UEQComponentInteraction::Interaction"));
}