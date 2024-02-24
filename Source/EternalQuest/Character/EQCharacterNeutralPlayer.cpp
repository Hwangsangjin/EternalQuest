// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayer.h"

#include "Blueprint/UserWidget.h"

AEQCharacterNeutralPlayer::AEQCharacterNeutralPlayer()
{
	ClothComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Cloth Component"));
	ClothComp->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
	GetMesh()->SetRelativeScale3D(FVector(2.5));
	
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
