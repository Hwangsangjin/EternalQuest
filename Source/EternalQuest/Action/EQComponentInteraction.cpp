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
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/EQItemBase.h"
#include "Player/EQPlayerController.h"
#include "Widget/EQWidgetInteract.h"
#include "Widget/EQWidgetMainUI.h"
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

	static ConstructorHelpers::FObjectFinder<UInputAction> EatItemRef(TEXT("/Game/LDJ/Inputs/IA_EatItem.IA_EatItem"));
	if (EatItemRef.Succeeded())
	{
		EatItemAction = EatItemRef.Object;
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
		EnhancedInputComponent->BindAction(EatItemAction, ETriggerEvent::Started, this, &UEQComponentInteraction::EatItem);
	}
}

void UEQComponentInteraction::Interaction()
{
	if (!NPC) return;
	PromptWidget->PullNPCInfomation(NPC);
	FInputModeGameAndUI InData;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	/////
	PromptWidget->AddToViewport();
}

void UEQComponentInteraction::EatItem()
{
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("UEQComponentInteraction::EatItem"));
}

void UEQComponentInteraction::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	NPC = Cast<AEQCharacterNeutralPlayer>(OtherActor);
	Item = Cast<AEQItemBase>(OtherActor);
	if (NPC)
	{
		NPC->GetMesh()->SetRenderCustomDepth(true);
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractDisable();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractShowNPC();
	}
	if (Item)
	{
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractDisable();
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractShowItem();
		Item->MeshComp->SetRenderCustomDepth(true);
	}
}

void UEQComponentInteraction::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	NPC = Cast<AEQCharacterNeutralPlayer>(OtherActor);
	Item = Cast<AEQItemBase>(OtherActor);
	if (NPC)
	{
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractDisable();
		NPC->GetMesh()->SetRenderCustomDepth(false);
		NPC = nullptr;
	}
	if (Item)
	{
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractDisable();
		Item->MeshComp->SetRenderCustomDepth(false);
		Item = nullptr;
	}
}
