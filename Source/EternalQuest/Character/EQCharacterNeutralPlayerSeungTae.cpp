// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerSeungTae.h"

#include "Blueprint/UserWidget.h"
#include "Component/EQComponentQuest.h"

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
	NPCName = TEXT("고브승태");
	NPCPrompt.PushLast(TEXT("안녕고브!, 넌 엘리시움에 못보던 얼굴인데 모험가인가봐?"));
	NPCPrompt.PushLast(TEXT("나는 서쪽광산에서 일하고 있는 고브승태 라고 해,"));
	NPCPrompt.PushLast(TEXT("갑작스럽지만, 지금 서쪽 광산에서 이상한 사건들이 발생하고 있어서\n못들어가고 있는데 혹시 서쪽광산을 조사해줄 수 있어? QuestTag"));
}

void AEQCharacterNeutralPlayerSeungTae::QuestAccepted()
{
	NPCPrompt.Reset();
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[0] == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[0] = 1;
	}
	NPCPrompt.PushLast(TEXT("이미 퀘스트를 받았잖아!"));
}

void AEQCharacterNeutralPlayerSeungTae::QuestDenied()
{
	GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red, TEXT("퀘스트를 거절했습니다."));
}
