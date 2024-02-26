// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerSeungTae.h"

#include "Blueprint/UserWidget.h"
#include "Component/EQComponentQuest.h"

AEQCharacterNeutralPlayerSeungTae::AEQCharacterNeutralPlayerSeungTae()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Game/Assets/Cute_Little_Animals/Piggy/Mesh/SK_Piggy.SK_Piggy"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ClothMeshRef(TEXT("/Game/Assets/Cute_Little_Animals/Piggy/Mesh/SK_Piggy_Clothes.SK_Piggy_Clothes"));
	if (ClothMeshRef.Succeeded())
	{
		ClothComp->SetSkeletalMesh(ClothMeshRef.Object);
	}
}

void AEQCharacterNeutralPlayerSeungTae::BeginPlay()
{
	Super::BeginPlay();
	NPCName = TEXT("승태");
	NPCPrompt.PushLast(TEXT("안녕!, 넌 엘리시움에 못보던 얼굴인데 모험가인가봐?"));
	NPCPrompt.PushLast(TEXT("나는 새싹광산에서 일하고 있는 승태 라고 해,"));
	NPCPrompt.PushLast(TEXT("일기장에 일기와 오늘의 할일을 써야 하는데 어디있는지 보이질 않어!"));
	NPCPrompt.PushLast(TEXT("근처에 떨군것 같은데, 혹시 네가 찾아줄 수 있어? QuestTag"));
}

void AEQCharacterNeutralPlayerSeungTae::QuestAccepted()
{
	NPCPrompt.Reset();
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[0] == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[0] = 1;
	}
	NPCPrompt.PushLast(TEXT("혹시 내 일기장을 못봤니?"));
}

void AEQCharacterNeutralPlayerSeungTae::QuestDenied()
{
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, TEXT("퀘스트를 거절했습니다."));
}
