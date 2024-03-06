// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQReturnTimer.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQReturnTimer : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI",meta=(BindWidget))
	UTextBlock* txt_Num;
	void CountToReturn(int32 Count);
};
