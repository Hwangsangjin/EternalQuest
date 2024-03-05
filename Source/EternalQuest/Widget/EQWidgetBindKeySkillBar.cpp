// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetBindKeySkillBar.h"

#include "Components/WidgetSwitcher.h"
#include "Game/EQGameInstance.h"

void UEQWidgetBindKeySkillBar::NativeConstruct()
{
	Super::NativeConstruct();

	auto EQClassType = Cast<UEQGameInstance>(GetWorld()->GetGameInstance())->GetClassType();

	if (EQClassType == EClassType::ECT_Warrior)
	{
		WS_JobSkillUI->SetActiveWidgetIndex(0);
	}
	else if (EQClassType == EClassType::ECT_Mage)
	{
		WS_JobSkillUI->SetActiveWidgetIndex(1);
	}
}
