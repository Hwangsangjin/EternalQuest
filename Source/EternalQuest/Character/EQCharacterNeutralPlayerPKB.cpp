// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerPKB.h"

#include "NiagaraComponent.h"
#include "Component/EQComponentQuest.h"

AEQCharacterNeutralPlayerPKB::AEQCharacterNeutralPlayerPKB()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Game/Assets/Cute_Little_Animals/Kitty/Mesh/SK_Kitty.SK_Kitty"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ClothMeshRef(TEXT("/Game/Assets/Cute_Little_Animals/Kitty/Mesh/SK_Kitty_Clothes.SK_Kitty_Clothes"));
	if (ClothMeshRef.Succeeded())
	{
		ClothComp->SetSkeletalMesh(ClothMeshRef.Object);
	}
}

void AEQCharacterNeutralPlayerPKB::BeginPlay()
{
	Super::BeginPlay();
	NPCName = TEXT("경복");
	NPCPrompt.PushLast(TEXT("승태한테 새로운 모험가가 왔다고 이야기는 들었어"));
	NPCPrompt.PushLast(TEXT("나는 VFX 대장장이 경복이라고 해"));
	NPCPrompt.PushLast(TEXT("마을에 나가서 내가 만든 새로운 펭귄소드를 시험해보려 하는데"));
	NPCPrompt.PushLast(TEXT("엄청 큰 전갈이 와서 내 펭귄 소드를 뺏어버렸지 뭐야?"));
	NPCPrompt.PushLast(TEXT("나 혼자서는 감당 못할것 같아서 네가 가져다줬으면 하는데"));
	NPCPrompt.PushLast(TEXT("혹시 가능하겠니?, 가져다주면 새로운 무기를 줄게! QuestTag"));
}

void AEQCharacterNeutralPlayerPKB::QuestAccepted()
{
	Super::QuestAccepted();
	NPCPrompt.Reset();
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[1] == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[1] = 1;
	}
	NPCPrompt.PushLast(TEXT("내 펭귄 소드..."));
	QuestIcon->SetVisibility(false);
}

void AEQCharacterNeutralPlayerPKB::QuestDenied()
{
	Super::QuestDenied();
}
