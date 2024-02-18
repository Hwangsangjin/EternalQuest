// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/EQComponentWidget.h"
#include "Widget/EQWidgetBase.h"

void UEQComponentWidget::InitWidget()
{
	Super::InitWidget();

	UEQWidgetBase* WidgetBase = Cast<UEQWidgetBase>(GetWidget());
	if (WidgetBase)
	{
		WidgetBase->SetOwningActor(GetOwner());
	}
}
