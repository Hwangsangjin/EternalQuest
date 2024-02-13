// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/EQComponentMenuManager.h"

#include "EnhancedInputComponent.h"

UEQComponentMenuManager::UEQComponentMenuManager()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> CallMenuRef(TEXT("/Game/LDJ/Inputs/IA_CallMenu.IA_CallMenu"));
	if (CallMenuRef.Object)
	{
		CallMenuAction = CallMenuRef.Object;
	}
}

void UEQComponentMenuManager::BeginPlay()
{
	Super::BeginPlay();
}

void UEQComponentMenuManager::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQComponentMenuManager::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(CallMenuAction, ETriggerEvent::Started, this, &UEQComponentMenuManager::CallMenu);
	}
}

void UEQComponentMenuManager::CallMenu(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, TEXT("CallMenu"));
}
