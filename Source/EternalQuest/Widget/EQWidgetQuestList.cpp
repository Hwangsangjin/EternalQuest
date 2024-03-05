// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetQuestList.h"

#include "Component/EQComponentQuest.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"

UEQWidgetQuestList::UEQWidgetQuestList(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> QuestIconClickSoundRef(TEXT("/Script/Engine.SoundWave'/Game/Assets/RPG_Interface_SFX/WAV/Interaction_With_Book_TurnPage_03.Interaction_With_Book_TurnPage_03'"));
	if (QuestIconClickSoundRef.Succeeded())
	{
		QuestIconClickSound = QuestIconClickSoundRef.Object;
	}
}

void UEQWidgetQuestList::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Quest1->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuest1);
	Btn_Quest2->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuest2);
	Btn_Quest3->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuest3);
	Btn_Quest4->OnClicked.AddDynamic(this, &ThisClass::OnClickedQuest4);

	QuestComp = GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>();
}

void UEQWidgetQuestList::OnClickedQuest1()
{
	PlaySound(QuestIconClickSound);
	Txt_QuestSubject->SetText(FText::FromString(TEXT("승태의 오늘의 할일 노트")));
	Txt_QuestDetail->SetText(FText::FromString(TEXT("승태의 일기장을 어디선가 떨구었다고 한다. \n\n아마 마을 어딘가에 있을것 같은데 잘 찾아주자.")));
	Txt_QuestProgress->SetText(FText::FromString(FString::Printf(TEXT("승태의 일기장 \n%d / 1"), QuestComp->QuestCondition.bQuestCond1)));
	
	if (QuestComp->QuestCondition.bQuestCond1)
	{
		Txt_QuestProgress->SetColorAndOpacity(FSlateColor(FColor::Green));
	}
	else
	{
		Txt_QuestProgress->SetColorAndOpacity(FSlateColor(FColor::White));
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[0] == 0)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 미완료")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[0] == 1)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 진행중")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[0] == 2)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 완료")));
	}
}

void UEQWidgetQuestList::OnClickedQuest2()
{
	PlaySound(QuestIconClickSound);

	Txt_QuestSubject->SetText(FText::FromString(TEXT("경복의 펭귄소드를 얻어라")));
	Txt_QuestDetail->SetText(FText::FromString(TEXT("경복의 펭귄소드를 거대전갈이 빼앗아갔다고 한다. \n\n거대 전갈을 해치우고 펭귄소드를 찾아주자.")));
	Txt_QuestProgress->SetText(FText::FromString(FString::Printf(TEXT("펭귄 소드 \n%d / 1"), QuestComp->QuestCondition.bQuestCond2)));
	
	if (QuestComp->QuestCondition.bQuestCond2)
	{
		Txt_QuestProgress->SetColorAndOpacity(FSlateColor(FColor::Green));
	}
	else
	{
		Txt_QuestProgress->SetColorAndOpacity(FSlateColor(FColor::White));
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[1] == 0)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 미완료")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[1] == 1)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 진행중")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[1] == 2)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 완료")));
	}
}

void UEQWidgetQuestList::OnClickedQuest3()
{
	PlaySound(QuestIconClickSound);

	Txt_QuestSubject->SetText(FText::FromString(TEXT("민경이의 안전한 자전거길")));
	Txt_QuestDetail->SetText(FText::FromString(TEXT("마을 바깥의 버섯들 때문에 민경이가 자전거를 탈 수 없다고 한다. \n\n버섯들을 해치워 자전거를 탈수 있는 안전한 길을 만들어주자.")));
	Txt_QuestProgress->SetText(FText::FromString(FString::Printf(TEXT("빨간 버섯의 보석 \n%d / 5"), QuestComp->QuestCondition.bQuestCond3Quantity)));

	if (QuestComp->QuestCondition.bQuestCond3)
	{
		Txt_QuestProgress->SetColorAndOpacity(FSlateColor(FColor::Green));
	}
	else
	{
		Txt_QuestProgress->SetColorAndOpacity(FSlateColor(FColor::White));
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[2] == 0)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 미완료")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[2] == 1)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 진행중")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[2] == 2)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 완료")));
	}
}

void UEQWidgetQuestList::OnClickedQuest4()
{
	PlaySound(QuestIconClickSound);

	Txt_QuestSubject->SetText(FText::FromString(TEXT("보스를 처치하고 새싹을 수료하자")));
	Txt_QuestDetail->SetText(FText::FromString(TEXT("이제 최종 프로젝트만 남았다. \n\n 오크 보스를 쓰러뜨리고, 새싹을 수료해보자.")));
	Txt_QuestProgress->SetText(FText::FromString(FString::Printf(TEXT("새싹 수료증 \n%d / 1"), QuestComp->QuestCondition.bQuestCond4)));

	if (QuestComp->QuestCondition.bQuestCond3)
	{
		Txt_QuestProgress->SetColorAndOpacity(FSlateColor(FColor::Green));
	}
	else
	{
		Txt_QuestProgress->SetColorAndOpacity(FSlateColor(FColor::White));
	}
	
	if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[3] == 0)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 미완료")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[3] == 1)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 진행중")));
	}
	else if (GetWorld()->GetFirstPlayerController()->GetCharacter()->FindComponentByClass<UEQComponentQuest>()->QuestCondition.QuestStateArray[3] == 2)
	{
		Txt_QuestState->SetText(FText::FromString(TEXT("퀘스트 완료")));
	}
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

void UEQWidgetQuestList::UpdateQuestIcon()
{
	OnClickedQuest2();
	OnClickedQuest3();
	OnClickedQuest4();
	OnClickedQuest1();
}
