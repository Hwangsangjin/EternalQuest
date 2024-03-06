// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerPKB.h"

#include "NiagaraComponent.h"
#include "Component/EQComponentQuest.h"
#include "Item/EQItemBase.h"

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
	NPCPrompt.PushLast(TEXT("마을에 나가서 내가 만든 새로운 펭귄빠따를 시험해보려 하는데"));
	NPCPrompt.PushLast(TEXT("엄청 큰 전갈이 와서 내 펭귄빠따를 뺏어버렸지 뭐야?"));
	NPCPrompt.PushLast(TEXT("나 혼자서는 감당 못할것 같아서 네가 가져다줬으면 하는데"));
	NPCPrompt.PushLast(TEXT("혹시 가능하겠니?, 가져다주면 새로운 무기를 줄게! QuestTag"));
}

void AEQCharacterNeutralPlayerPKB::QuestAccepted()
{
	Super::QuestAccepted();
	NPCPrompt.Reset();
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[1] == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[1] = 1;
	}
	NPCPrompt.PushLast(TEXT("내 펭귄 빠따..."));
	QuestIcon->SetVisibility(false);
}

void AEQCharacterNeutralPlayerPKB::QuestDenied()
{
	Super::QuestDenied();
}

void AEQCharacterNeutralPlayerPKB::QuestSuccess()
{
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[1] == 2)
	{
		NPCPrompt.Reset();
		NPCPrompt.PushLast(TEXT("역시 고양이보단 펭귄이지~"));
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[1] != 1)
	{
		Super::QuestSuccess();
		return;
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.bQuestCond2 != true)
	{
		Super::QuestSuccess();
		return;
	}
	
	NPCPrompt.Reset();
	NPCPrompt.PushLast(TEXT("내 펭귄빠따를 찾아주었구나! 고마워, 이건 내 혼이 담긴 새싹혼 무기야."));
	auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
	if (CurrItem)
	{
		CurrItem->ItemName.DataTable = ItemDataTable;
		CurrItem->ItemName.RowName = TEXT("SeSacSoulWand");
		CurrItem->ItemType = EEQItemType::Equipment;
		CurrItem->ItemQuantity = 1;
	}
	CurrItem->FinishSpawning(GetActorTransform());

	GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[1] = 2;

	Super::QuestSuccess();
}
