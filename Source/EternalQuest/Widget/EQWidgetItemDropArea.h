// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetItemDropArea.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetItemDropArea : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};
