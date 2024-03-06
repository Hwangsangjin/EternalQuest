// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EQWidgetUserName.h"
#include "Components/TextBlock.h"
#include "Character/EQCharacterPlayer.h"
#include "Interface/EQInterfaceCharacterWidget.h"

UEQWidgetUserName::UEQWidgetUserName(const FObjectInitializer& ObjectInitialzer)
	: Super(ObjectInitialzer)
{
}

void UEQWidgetUserName::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlock_UserName->SetText(Cast<AEQCharacterPlayer>(OwningActor)->GetUserName());
	ensure(TextBlock_UserName);

	IEQInterfaceCharacterWidget* CharacterWidget = Cast<IEQInterfaceCharacterWidget>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}
