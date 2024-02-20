// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "EQItemDragDropOperation.generated.h"

class UEQWidgetItemSlot;
struct FEQSlot;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UEQWidgetItemSlot* EQWidgetItemSlot;
	
	FEQSlot* EQSlot;
};
