// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentQuest.h"

#include "EQComponentInventory.h"
#include "GameFramework/Character.h"
#include "Player/EQPlayerController.h"

UEQComponentQuest::UEQComponentQuest()
{
	for (int i = 0; i < 4; i++) QuestStateArray.Push(0); // 나중에 퀘스트 진척도 변경하기
}

void UEQComponentQuest::BeginPlay()
{
	Super::BeginPlay();
	// for (int i = 0; i < 4; i++) QuestStateArray.Push(0); // 나중에 퀘스트 진척도 변경하기
}

void UEQComponentQuest::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEQComponentQuest::InspectingItem()
{
	auto Inventory = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentInventory>();
	for (int i = 0; i < Inventory->EQAllItem.QuestItem.Num(); i++)
	{
		if (Inventory->EQAllItem.QuestItem[i].ItemID.RowName == TEXT("ST_Diary"))
		{
			bQuestCond1 = true;
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("퀘스트1 완료!"));
		}

		if (Inventory->EQAllItem.QuestItem[i].ItemID.RowName == TEXT("PenguinSword"))
		{
			bQuestCond2 = true;
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("퀘스트2 완료!"));
		}
		
		if (Inventory->EQAllItem.QuestItem[i].ItemID.RowName == TEXT("MushRoomGem") && Inventory->EQAllItem.QuestItem[i].Quantity > 4)
		{
			bQuestCond3 = true;
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("퀘스트3 완료!"));
		}

		if (Inventory->EQAllItem.QuestItem[i].ItemID.RowName == TEXT("OrcTooth"))
		{
			bQuestCond4 = true;
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("퀘스트4 완료!"));
		}
	}
}
