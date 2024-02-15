// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/EQComponentInventory.h"

#include "EnhancedInputComponent.h"
#include "Character/EQCharacterPlayer.h"
#include "Item/EQItemBase.h"
#include "Kismet/KismetSystemLibrary.h"

UEQComponentInventory::UEQComponentInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEQComponentInventory::BeginPlay()
{
	Super::BeginPlay();

	FItemSlot* Result = ItemID->FindRow<FItemSlot>(FName("TestItem"), "");
}

void UEQComponentInventory::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQComponentInventory::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);
	
}
