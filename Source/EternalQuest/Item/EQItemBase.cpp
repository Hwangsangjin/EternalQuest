// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EQItemBase.h"


// Sets default values
AEQItemBase::AEQItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(MeshComp);
}

void AEQItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEQItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

