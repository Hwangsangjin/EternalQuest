// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerSMK.h"

#include "NiagaraComponent.h"
#include "Component/EQComponentQuest.h"
#include "Item/EQItemBase.h"

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
	NPCPrompt.PushLast(TEXT("혹시 마을 밖에 있는 버섯들 5마리만 좀 처리해줄 수 있어?"));
	NPCPrompt.PushLast(TEXT("처리하고 빨간 버섯의 보석을 5개만 가져다 줘! QuestTag"));
}

void AEQCharacterNeutralPlayerSMK::QuestAccepted()
{
	Super::QuestAccepted();
	NPCPrompt.Reset();
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[2] == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[2] = 1;
	}
	NPCPrompt.PushLast(TEXT("혹시, 처리는 다 했니?"));
	QuestIcon->SetVisibility(false);
}

void AEQCharacterNeutralPlayerSMK::QuestDenied()
{
	Super::QuestDenied();
}

void AEQCharacterNeutralPlayerSMK::QuestSuccess()
{
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[2] == 2)
	{
		NPCPrompt.Reset();
		NPCPrompt.PushLast(TEXT("이제 맘놓고 자전거를 탈 수 있겠어!"));
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[2] != 1)
	{
		Super::QuestSuccess();
		return;
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.bQuestCond3 != true)
	{
		Super::QuestSuccess();
		return;
	}
	
	NPCPrompt.Reset();
	NPCPrompt.PushLast(TEXT("드디어 버섯들을 다 처치했구나! 고마워 이건 내 선물이야 잘 써!"));
	auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
	if (CurrItem)
	{
		CurrItem->ItemName.DataTable = ItemDataTable;
		CurrItem->ItemName.RowName = TEXT("SeSacSoulShield");
		CurrItem->ItemType = EEQItemType::Equipment;
		CurrItem->ItemQuantity = 1;
	}
	CurrItem->FinishSpawning(GetActorTransform());

	GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[2] = 2;
	
	Super::QuestSuccess();
}
