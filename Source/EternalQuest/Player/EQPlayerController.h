// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EQPlayerController.generated.h"

class UEQWidgetMainUI;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AEQPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MySettings)
	TSubclassOf<UEQWidgetMainUI> MainUIFactory;

	UPROPERTY()
	TObjectPtr<UEQWidgetMainUI> EQWidgetMainUI;
};
