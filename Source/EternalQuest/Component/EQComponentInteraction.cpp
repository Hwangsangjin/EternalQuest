// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentInteraction.h"

#include "EnhancedInputComponent.h"
#include "EQComponentInventory.h"
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
#include "Widget/EQWidgetInventory.h"
#include "Widget/EQWidgetMainUI.h"
#include "Widget/EQWidgetNpcPrompt.h"

UEQComponentInteraction::UEQComponentInteraction()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionActionRef(TEXT("/Game/Blueprints/Input/Actions/IA_Interaction.IA_Interaction"));
	if (InteractionActionRef.Object)
	{
		InteractionAction = InteractionActionRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PromptWidgetFactoryRef(TEXT("/Game/Blueprints/UI/WBP_EQWidgetNpcPrompt.WBP_EQWidgetNpcPrompt_C"));
	if (PromptWidgetFactoryRef.Succeeded())
	{
		PromptWidgetFactory = PromptWidgetFactoryRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> EatItemRef(TEXT("/Game/Blueprints/Input/Actions/IA_EatItem.IA_EatItem"));
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
	if (Item)
	{
		GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,TEXT("UEQComponentInteraction::EatItem"));
		if (AddToInventory(Item->Slot))
		{
			Item->Destroy();
			EQPlayerController->EQWidgetMainUI->WBP_EQWidgetInventory->UpdateItemInInventoryUI();
		}
	}
}

bool UEQComponentInteraction::AddToInventory(const FEQSlot& InSlot)
{
	if (InSlot.ItemType == EEQItemType::Equipment)
	{
		for (int i = 0; i < EQComponentInventory->EQAllItem.Equipment.Num(); i++)
		{
			if (Item->Slot.ItemID.RowName == EQComponentInventory->EQAllItem.Equipment[i].ItemID.RowName)
			{
				auto OutRow = Item->Slot.ItemID.DataTable->FindRow<FEQItem>(Item->Slot.ItemID.RowName, "");
				if (OutRow->StackSize >= (Item->Slot.Quantity + EQComponentInventory->EQAllItem.Equipment[i].Quantity))
				{
					EQComponentInventory->EQAllItem.Equipment[i].Quantity = (Item->Slot.Quantity + EQComponentInventory
						->EQAllItem.Equipment[i].Quantity);
					return true;
				}
			}
		}

		for	(int i = 0; i < EQComponentInventory->EQAllItem.Equipment.Num(); i++)
		{
			if(EQComponentInventory->EQAllItem.Equipment[i].Quantity == 0)
			{
				EQComponentInventory->EQAllItem.Equipment[i] = Item->Slot;
				return true;
			}
		}
		return false;
	}
	
	else if(InSlot.ItemType == EEQItemType::Consumtion)
	{
		for (int i = 0; i < EQComponentInventory->EQAllItem.Consumtion.Num(); i++)
		{
			if (Item->Slot.ItemID.RowName == EQComponentInventory->EQAllItem.Consumtion[i].ItemID.RowName)
			{
				auto OutRow = Item->Slot.ItemID.DataTable->FindRow<FEQItem>(Item->Slot.ItemID.RowName, "");
				if (OutRow->StackSize >= (Item->Slot.Quantity + EQComponentInventory->EQAllItem.Consumtion[i].Quantity))
				{
					EQComponentInventory->EQAllItem.Consumtion[i].Quantity = (Item->Slot.Quantity + EQComponentInventory
						->EQAllItem.Consumtion[i].Quantity);
					return true;
				}
			}
		}

		for	(int i = 0; i < EQComponentInventory->EQAllItem.Consumtion.Num(); i++)
		{
			if(EQComponentInventory->EQAllItem.Consumtion[i].Quantity == 0)
			{
				EQComponentInventory->EQAllItem.Consumtion[i] = Item->Slot;
				return true;
			}
		}

		return false;
	}
	else if(InSlot.ItemType == EEQItemType::Material)
	{
		for (int i = 0; i < EQComponentInventory->EQAllItem.Material.Num(); i++)
		{
			if (Item->Slot.ItemID.RowName == EQComponentInventory->EQAllItem.Material[i].ItemID.RowName)
			{
				auto OutRow = Item->Slot.ItemID.DataTable->FindRow<FEQItem>(Item->Slot.ItemID.RowName, "");
				if (OutRow->StackSize >= (Item->Slot.Quantity + EQComponentInventory->EQAllItem.Material[i].Quantity))
				{
					EQComponentInventory->EQAllItem.Material[i].Quantity = (Item->Slot.Quantity + EQComponentInventory
						->EQAllItem.Material[i].Quantity);
					return true;
				}
			}
		}

		for	(int i = 0; i < EQComponentInventory->EQAllItem.Material.Num(); i++)
		{
			if(EQComponentInventory->EQAllItem.Material[i].Quantity == 0)
			{
				EQComponentInventory->EQAllItem.Material[i] = Item->Slot;
				return true;
			}
		}

		return false;
	}
	else if(InSlot.ItemType == EEQItemType::Questitem)
	{
		for (int i = 0; i < EQComponentInventory->EQAllItem.QuestItem.Num(); i++)
		{
			if (Item->Slot.ItemID.RowName == EQComponentInventory->EQAllItem.QuestItem[i].ItemID.RowName)
			{
				auto OutRow = Item->Slot.ItemID.DataTable->FindRow<FEQItem>(Item->Slot.ItemID.RowName, "");
				if (OutRow->StackSize >= (Item->Slot.Quantity + EQComponentInventory->EQAllItem.QuestItem[i].Quantity))
				{
					EQComponentInventory->EQAllItem.QuestItem[i].Quantity = (Item->Slot.Quantity + EQComponentInventory
						->EQAllItem.QuestItem[i].Quantity);
					return true;
				}
			}
		}

		for	(int i = 0; i < EQComponentInventory->EQAllItem.QuestItem.Num(); i++)
		{
			if(EQComponentInventory->EQAllItem.QuestItem[i].Quantity == 0)
			{
				EQComponentInventory->EQAllItem.QuestItem[i] = Item->Slot;
				return true;
			}
		}
		return false;
	}
	return false;
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
