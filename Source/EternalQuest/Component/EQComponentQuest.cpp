// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentQuest.h"

#include "EQComponentInventory.h"
#include "GameFramework/Character.h"
#include "Player/EQPlayerController.h"

UEQComponentQuest::UEQComponentQuest()
{
	
}

void UEQComponentQuest::BeginPlay()
{
	Super::BeginPlay();
	
	if (QuestCondition.QuestStateArray.IsEmpty())
	{
		for (int i = 0; i < 4; i++) QuestCondition.QuestStateArray.Push(0); // 나중에 퀘스트 진척도 변경하기
	}
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
			QuestCondition.bQuestCond1 = true;
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("퀘스트1 완료!"));
		}

		if (Inventory->EQAllItem.QuestItem[i].ItemID.RowName == TEXT("PenguinSword"))
		{
			QuestCondition.bQuestCond2 = true;
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("퀘스트2 완료!"));
		}

		if (Inventory->EQAllItem.QuestItem[i].ItemID.RowName == TEXT("MushRoomGem"))
		{
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Magenta, TEXT("1111111111111111111"));
			QuestCondition.bQuestCond3Quantity = Inventory->EQAllItem.QuestItem[i].Quantity;
		}
		
		if (Inventory->EQAllItem.QuestItem[i].ItemID.RowName == TEXT("MushRoomGem") && Inventory->EQAllItem.QuestItem[i].Quantity > 4)
		{
			QuestCondition.bQuestCond3 = true;
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("퀘스트3 완료!"));
		}

		if (Inventory->EQAllItem.QuestItem[i].ItemID.RowName == TEXT("OrcTooth"))
		{
			QuestCondition.bQuestCond4 = true;
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, TEXT("퀘스트4 완료!"));
		}
	}
}
