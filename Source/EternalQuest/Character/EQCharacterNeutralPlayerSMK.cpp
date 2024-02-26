// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerSMK.h"

#include "Component/EQComponentQuest.h"

AEQCharacterNeutralPlayerSMK::AEQCharacterNeutralPlayerSMK()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Game/Assets/Cute_Little_Animals/Bunny/Mesh/SK_Bunny.SK_Bunny"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ClothMeshRef(TEXT("/Game/Assets/Cute_Little_Animals/Bunny/Mesh/SK_Bunny_Clothes.SK_Bunny_Clothes"));
	if (ClothMeshRef.Succeeded())
	{
		ClothComp->SetSkeletalMesh(ClothMeshRef.Object);
	}
}

void AEQCharacterNeutralPlayerSMK::BeginPlay()
{
	Super::BeginPlay();
	NPCName = TEXT("민경");
	NPCPrompt.PushLast(TEXT("안녕? 네가 경복이가 말했던 모험가구나?"));
	NPCPrompt.PushLast(TEXT("일 잘하기로 소문이 자자하던데, 내 부탁좀 들어줄 수 있겠어?"));
	NPCPrompt.PushLast(TEXT("마을 밖에서 자전거를 타고 달리다가, 버섯돌이들이 너무 많아서 그만 넘어져버렸지 뭐야?"));
	NPCPrompt.PushLast(TEXT("자전거가 타고싶은데 버섯들 때문에 무서워서 탈수가 없어"));
	NPCPrompt.PushLast(TEXT("혹시 마을 밖에 있는 버섯들 5마리만 좀 처리해줄 수 있어? QuestTag"));
}

void AEQCharacterNeutralPlayerSMK::QuestAccepted()
{
	Super::QuestAccepted();
	NPCPrompt.Reset();
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[2] == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[2] = 1;
	}
	NPCPrompt.PushLast(TEXT("혹시, 처리는 다 했니?"));
}

void AEQCharacterNeutralPlayerSMK::QuestDenied()
{
	Super::QuestDenied();
}
