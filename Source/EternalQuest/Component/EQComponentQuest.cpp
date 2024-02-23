// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentQuest.h"

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
