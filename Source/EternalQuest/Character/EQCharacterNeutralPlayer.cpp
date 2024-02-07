// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayer.h"

AEQCharacterNeutralPlayer::AEQCharacterNeutralPlayer()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Game/Assets/CasualFantasyMonster/Meshes/Goblin03/SK_Goblin3.SK_Goblin3"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
}

void AEQCharacterNeutralPlayer::BeginPlay()
{
	Super::BeginPlay();
}
