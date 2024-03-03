// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentInteraction.h"

#include "EnhancedInputComponent.h"
#include "EQComponentInventory.h"
#include "EQComponentQuest.h"
#include "Blueprint/UserWidget.h"
#include "Character/EQCharacterNeutralPlayer.h"
#include "Character/EQCharacterNonPlayer.h"
#include "Character/EQCharacterPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextBlock.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/EQItemBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Player/EQPlayerController.h"
#include "Widget/EQWidgetInteract.h"
#include "Widget/EQWidgetInventory.h"
#include "Widget/EQWidgetItemLoger.h"
#include "Widget/EQWidgetMainUI.h"
#include "Widget/EQWidgetNpcPrompt.h"

UEQComponentInteraction::UEQComponentInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionActionRef(
		TEXT("/Game/Blueprints/Input/Actions/IA_Interaction.IA_Interaction"));
	if (InteractionActionRef.Object)
	{
		InteractionAction = InteractionActionRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PromptWidgetFactoryRef(
		TEXT("/Game/Blueprints/UI/WBP_EQWidgetNpcPrompt.WBP_EQWidgetNpcPrompt_C"));
	if (PromptWidgetFactoryRef.Succeeded())
	{
		PromptWidgetFactory = PromptWidgetFactoryRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> EatItemRef(
		TEXT("/Game/Blueprints/Input/Actions/IA_EatItem.IA_EatItem"));
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
	EQComponentInventory = Player->FindComponentByClass<UEQComponentInventory>();
}

void UEQComponentInteraction::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
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
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this,
		                                   &UEQComponentInteraction::Interaction);
		EnhancedInputComponent->BindAction(EatItemAction, ETriggerEvent::Started, this,
		                                   &UEQComponentInteraction::EatItem);
	}
}

void UEQComponentInteraction::Interaction()
{
	if (!NPC || bCommunicationNPC) return;
	PromptWidget->DisplayText = TEXT("");
	auto LookValue = UKismetMathLibrary::FindLookAtRotation(NPC->GetActorLocation(), GetOwner()->GetActorLocation());
	NPC->SetActorRotation(LookValue);
	
	PromptWidget->PullNPCInfomation(NPC);
	bCommunicationNPC = true;
	FInputModeGameAndUI InData;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InData);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	PromptWidget->AddToViewport();
}

void UEQComponentInteraction::EatItem()
{
	if (IsValid(Item))
	{
		EQComponentInventory->AddToInventory(Item->Slot); // 인벤토리에 추가하기
		EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInventory->UpdateItemInInventoryUI(); // 인벤토리 업데이트
		Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->WBP_EQWidgetItemLoger->SetItemLogMessage(Item->Slot); // 아이템 로그 띄우기
		auto QuestComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>();
		QuestComp->InspectingItem();
		ServerRPC_EatItem();
	}
}

void UEQComponentInteraction::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                const FHitResult& SweepResult)
{
	NPC = Cast<AEQCharacterNeutralPlayer>(OtherActor);
	Item = Cast<AEQItemBase>(OtherActor);
	if (NPC)
	{
		NPC->GetMesh()->SetRenderCustomDepth(true);
		if (Cast<AEQCharacterPlayer>(GetOwner())->IsLocallyControlled())
		{
			EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractDisable();
			EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractShowNPC();
		}
	}
	if (Item)
	{
		Item->MeshComp->SetRenderCustomDepth(true);
		if (Cast<AEQCharacterPlayer>(GetOwner())->IsLocallyControlled())
		{
			EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractDisable();
			EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractShowItem();
		}
	}
}

void UEQComponentInteraction::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	NPC = Cast<AEQCharacterNeutralPlayer>(OtherActor);
	Item = Cast<AEQItemBase>(OtherActor);
	if (NPC)
	{
		if (Cast<AEQCharacterPlayer>(GetOwner())->IsLocallyControlled())
		{
			EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractDisable();
		}
		NPC->GetMesh()->SetRenderCustomDepth(false);
		NPC = nullptr;
	}
	if (Item)
	{
		if (Cast<AEQCharacterPlayer>(GetOwner())->IsLocallyControlled())
		{
			EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInteract->InteractDisable();
		}
		Item->MeshComp->SetRenderCustomDepth(false);
		Item = nullptr;
	}
}

void UEQComponentInteraction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEQComponentInteraction, Item);
}

void UEQComponentInteraction::MultiRPC_EatItem_Implementation()
{
}

void UEQComponentInteraction::ServerRPC_EatItem_Implementation()
{
	if (Item)
	{
		Item->Destroy();
	}
}
