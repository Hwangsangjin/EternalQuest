// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EQComponentWidget.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQComponentWidget : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
};
