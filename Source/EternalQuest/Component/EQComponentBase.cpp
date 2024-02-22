// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentBase.h"

#include "Character/EQCharacterBase.h"
#include "Character/EQCharacterPlayer.h"
#include "Player/EQPlayerController.h"

// Sets default values for this component's properties
UEQComponentBase::UEQComponentBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
	//SetIsReplicated(true);
}


// Called when the game starts
void UEQComponentBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEQComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEQComponentBase::InitializeComponent()
{
	Super::InitializeComponent();
	Player = Cast<AEQCharacterPlayer>(GetOwner());
	Player->InputSignature.AddUObject(this, &UEQComponentBase::SetupPlayerInput);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
	{
		EQPlayerController = Cast<AEQPlayerController>(GetWorld()->GetFirstPlayerController());
	}), 0.1, false, 0.1);
}

void UEQComponentBase::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
}

