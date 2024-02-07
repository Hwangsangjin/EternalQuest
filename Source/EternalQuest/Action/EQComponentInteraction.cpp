// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/EQComponentInteraction.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Character/EQCharacterNeutralPlayer.h"
#include "Character/EQCharacterNonPlayer.h"
#include "Character/EQCharacterPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "Widget/EQWidgetNpcPrompt.h"

UEQComponentInteraction::UEQComponentInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionActionRef(TEXT("/Game/LDJ/Inputs/IA_Interaction.IA_Interaction"));
	if (InteractionActionRef.Object)
	{
		InteractionAction = InteractionActionRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PromptWidgetFactoryRef(TEXT("/Game/LDJ/UI/WBP_EQWidgetNpcPrompt.WBP_EQWidgetNpcPrompt_C"));
	if (PromptWidgetFactoryRef.Succeeded())
	{
		PromptWidgetFactory = PromptWidgetFactoryRef.Class;
	}
}

void UEQComponentInteraction::BeginPlay()
{
	Super::BeginPlay();
	Player->GetInteractionBox()->OnComponentBeginOverlap.AddDynamic(this, &UEQComponentInteraction::OnBoxBeginOverlap);
	Player->GetInteractionBox()->OnComponentEndOverlap.AddDynamic(this, &UEQComponentInteraction::OnBoxEndOverlap);
	PromptWidget = Cast<UEQWidgetNpcPrompt>(CreateWidget(GetWorld(), PromptWidgetFactory));
}

void UEQComponentInteraction::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQComponentInteraction::InitializeComponent()
{
	Super::InitializeComponent();
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
	if (!NPC) return;
	PromptWidget->PullNPCInfomation(NPC);
	FInputModeUIOnly InData;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	/////
	PromptWidget->AddToViewport();
}

void UEQComponentInteraction::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	NPC = Cast<AEQCharacterNeutralPlayer>(OtherActor);
	if (NPC)
	{
		NPC->GetMesh()->SetRenderCustomDepth(true);
	}
}

void UEQComponentInteraction::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	NPC = Cast<AEQCharacterNeutralPlayer>(OtherActor);
	if (NPC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("OnBoxEndOverlap"));
		NPC->GetMesh()->SetRenderCustomDepth(false);
		NPC = nullptr;
	}
}
