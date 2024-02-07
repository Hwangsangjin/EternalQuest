// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerSeungTae.h"

#include "Blueprint/UserWidget.h"

AEQCharacterNeutralPlayerSeungTae::AEQCharacterNeutralPlayerSeungTae()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Game/Assets/CasualFantasyMonster/Meshes/Goblin03/SK_Goblin3.SK_Goblin3"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
}

void AEQCharacterNeutralPlayerSeungTae::BeginPlay()
{
	Super::BeginPlay();
	NPCName = TEXT("김승태");
	NPCPrompt.PushLast(TEXT("행님, 버거형이 코볼트의 어금니 10개만 모아오래요"));
	NPCPrompt.PushLast(TEXT("QuestTag"));
	NPCPrompt.PushLast(TEXT("저는 쥬신 가볼게요, 버거형이 깜지써오래요."));
	NPCPrompt.PushLast(TEXT("다음에 국밥 한사바리 하시죠."));
}

void AEQCharacterNeutralPlayerSeungTae::PlayPrompt()
{
	Super::PlayPrompt();
}
