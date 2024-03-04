// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetMinimap.generated.h"

class UBorder;
class UImage;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetMinimap : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetMinimap(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Minimap_Mask;
};
