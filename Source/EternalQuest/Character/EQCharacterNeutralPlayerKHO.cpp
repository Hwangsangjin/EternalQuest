// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EQCharacterNeutralPlayerKHO.h"

#include "Component/EQComponentInventory.h"
#include "Component/EQComponentQuest.h"
#include "Item/EQItemBase.h"

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
	NPCName = TEXT("새싹 매니저님");
	NPCPrompt.PushLast(TEXT("안녕? 나는 새싹 길드를 운영하고 있는 매니저라고해."));
	NPCPrompt.PushLast(TEXT("실은 내가 소중하게 여기던 새싹 수료증을 오크무리들한테 뺏겨버렸지 뭐야?"));
	NPCPrompt.PushLast(TEXT("오크무리들은 깊은 던전속으로 들어가서 나혼자서는 도저히 들어갈수가 없었어..."));
	NPCPrompt.PushLast(TEXT("오크무리들을 정리하고 증표로 오크의 이빨을 가져다 줄 수 있을까?"));
	NPCPrompt.PushLast(TEXT("\n\n\n (수락 시, 던전으로 이동됩니다.) QuestTag"));
}

void AEQCharacterNeutralPlayerKHO::QuestAccepted()
{
	Super::QuestAccepted();
	NPCPrompt.Reset();
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[3] == 0)
	{
		GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[3] = 1;
	}
	NPCPrompt.PushLast(TEXT("던전에서 수료증을 가져와줘!"));

	GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>()->SaveInventory();
	
	if (HasAuthority())
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FString PathToLevel = FString("/Game/Maps/DungeonMap?listen");
			World->ServerTravel(PathToLevel);
		}
	}
}

void AEQCharacterNeutralPlayerKHO::QuestDenied()
{
	Super::QuestDenied();
}

void AEQCharacterNeutralPlayerKHO::QuestSuccess()
{

	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[3] == 2)
	{
		NPCPrompt.Reset();
		NPCPrompt.PushLast(TEXT("수료를 축하드려요!"));
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[3] != 1)
	{
		Super::QuestSuccess();
		return;
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->bQuestCond4 != true)
	{
		Super::QuestSuccess();
		return;
	}
	
	NPCPrompt.Reset();
	NPCPrompt.PushLast(TEXT("새싹 수료증은 사실 너희에게 주려고 한 거였어."));
	NPCPrompt.PushLast(TEXT("이 수료증을 받으면 꼭 취업할 수 있을거야."));
	auto CurrItem = GetWorld()->SpawnActorDeferred<AEQItemBase>(SpawnItemFactory, GetActorTransform());
	if (CurrItem)
	{
		CurrItem->ItemName.DataTable = ItemDataTable;
		CurrItem->ItemName.RowName = TEXT("SeSacCertificates");
		CurrItem->ItemType = EEQItemType::Questitem;
		CurrItem->ItemQuantity = 1;
	}
	CurrItem->FinishSpawning(GetActorTransform());

	GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[3] = 2;
	
	Super::QuestSuccess();
}
