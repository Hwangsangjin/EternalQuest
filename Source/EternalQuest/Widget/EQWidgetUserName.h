// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EQWidgetBase.h"
#include "EQWidgetUserName.generated.h"

class UTextBlock;

UCLASS()
class ETERNALQUEST_API UEQWidgetUserName : public UEQWidgetBase
{
	GENERATED_BODY()
	
public:
	UEQWidgetUserName(const FObjectInitializer& ObjectInitialzer);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	TObjectPtr<UTextBlock> TextBlock_UserName;
};
