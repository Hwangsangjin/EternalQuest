// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerKHO.h"

#include "Component/EQComponentQuest.h"

AEQCharacterNeutralPlayerKHO::AEQCharacterNeutralPlayerKHO()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Cute_Little_Animals/Doggy/Mesh/SK_Doggy.SK_Doggy'"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ClothMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Cute_Little_Animals/Doggy/Mesh/SK_Doggy_clothes.SK_Doggy_clothes'"));
	if (ClothMeshRef.Succeeded())
	{
		ClothComp->SetSkeletalMesh(ClothMeshRef.Object);
	}
}

void AEQCharacterNeutralPlayerKHO::BeginPlay()
{
	Super::BeginPlay();
	NPCName = TEXT("새싹 매니저");
	NPCPrompt.PushLast(TEXT("안녕? 나는 새싹 길드를 운영하고 있는 매니저라고해."));
	NPCPrompt.PushLast(TEXT("실은 내가 소중하게 여기던 새싹 수료증을 오크무리들한테 뺏겨버렸지 뭐야?"));
	NPCPrompt.PushLast(TEXT("오크무리들은 깊은 던전속으로 들어가서 나혼자서는 도저히 들어갈수가 없었어..."));
	NPCPrompt.PushLast(TEXT("혹시, 던전에서 수료증을 가져와 줄 수 있을까? \n\n\n (수락 시, 던전으로 이동됩니다.) QuestTag"));
}

void AEQCharacterNeutralPlayerKHO::QuestAccepted()
{
	Super::QuestAccepted();
	NPCPrompt.Reset();
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[3] == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[3] = 1;
	}
	NPCPrompt.PushLast(TEXT("혹시 내 일기장을 못봤니?"));
}

void AEQCharacterNeutralPlayerKHO::QuestDenied()
{
	Super::QuestDenied();
}
