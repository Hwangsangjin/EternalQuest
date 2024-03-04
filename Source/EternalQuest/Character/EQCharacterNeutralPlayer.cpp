// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayer.h"

#include "NiagaraComponent.h"
#include "Player/EQPlayerController.h"
#include "Widget/EQWidgetMainUI.h"

AEQCharacterNeutralPlayer::AEQCharacterNeutralPlayer()
{
	ClothComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Cloth Component"));
	ClothComp->SetupAttachment(GetMesh());
	ClothComp->bHiddenInSceneCapture = true;

	QuestIcon = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Quest Icon Component"));
	QuestIcon->SetupAttachment(RootComponent);
	QuestIcon->SetRelativeLocation(FVector(0,0,110));
	QuestIcon->bHiddenInSceneCapture = true;

	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
	GetMesh()->SetRelativeScale3D(FVector(2.5));
	GetMesh()->bHiddenInSceneCapture = true;

	static ConstructorHelpers::FClassFinder<AActor> SpawnItemFactoryRef(TEXT("/Game/Blueprints/Item/BP_EQItem.BP_EQItem_C"));
	if (SpawnItemFactoryRef.Succeeded()) SpawnItemFactory = SpawnItemFactoryRef.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> DTItemRef(TEXT("/Game/Blueprints/Data/DT_Item.DT_Item"));
	if (DTItemRef.Succeeded())
	{
		ItemDataTable = DTItemRef.Object;
	}
}

void AEQCharacterNeutralPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AEQCharacterNeutralPlayer::QuestAccepted()
{
}

void AEQCharacterNeutralPlayer::QuestDenied()
{
}

void AEQCharacterNeutralPlayer::QuestSuccess()
{
	Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController())->EQWidgetMainUI->SetVisibility(ESlateVisibility::Visible);
}
