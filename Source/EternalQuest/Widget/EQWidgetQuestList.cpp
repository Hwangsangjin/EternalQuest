// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetQuestList.h"

#include "Component/EQComponentQuest.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"

void UEQWidgetQuestList::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Quest1->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuest1);
	Btn_Quest2->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuest2);
	Btn_Quest3->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuest3);
	Btn_Quest4->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuest4);
	
}

void UEQWidgetQuestList::OnClickedQuest1()
{
	Txt_QuestSubject->SetText(FText::FromString(TEXT("승태의 오늘의 할일 노트")));
	Txt_QuestDetail->SetText(FText::FromString(TEXT("ㅁㄴㅇ")));
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[0] == 0)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 미완료")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[0] == 1)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 진행중")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestStateArray[0] == 2)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 완료")));
	}
}

void UEQWidgetQuestList::OnClickedQuest2()
{
	Txt_QuestSubject->SetText(FText::FromString(TEXT("경복의 펭귄소드를 얻어라")));
	Txt_QuestDetail->SetText(FText::FromString(TEXT("ㅁㄴㅇ")));
	Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 미완료")));
}

void UEQWidgetQuestList::OnClickedQuest3()
{
	Txt_QuestSubject->SetText(FText::FromString(TEXT("민경의 자전거를 되찾아라")));
	Txt_QuestDetail->SetText(FText::FromString(TEXT("ㅁㄴㅇ")));
	Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 미완료")));
}

void UEQWidgetQuestList::OnClickedQuest4()
{
	Txt_QuestSubject->SetText(FText::FromString(TEXT("보스를 처치하고 새싹을 수료하자")));
	Txt_QuestDetail->SetText(FText::FromString(TEXT("ㅁㄴㅇ")));
	Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 미완료")));
}

void UEQWidgetQuestList::ClearQuestIcon()
{
	if (bOpenQuest1)
	{
		bOpenQuest1 = false;
	}
	if (bOpenQuest2)
	{
		bOpenQuest2 = false;
	};
	if (bOpenQuest3)
	{
		bOpenQuest3 = false;
	}
	if (bOpenQuest4)
	{
		bOpenQuest4 = false;
	}
}
