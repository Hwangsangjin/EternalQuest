// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EQPlayerController.generated.h"

class UEQWidgetInventory;
class UEQWidgetMainUI;

DECLARE_MULTICAST_DELEGATE(FOnSeamlessCompleted);

UCLASS()
class ETERNALQUEST_API AEQPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEQPlayerController();

protected:
	virtual void PostInitializeComponents() override;
	virtual void PostNetInit() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostSeamlessTravel() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Replicated,Category=MySettings)
	TSubclassOf<UEQWidgetMainUI> MainUIFactory;

	UPROPERTY()
	TObjectPtr<UEQWidgetMainUI> EQWidgetMainUI;

	FOnSeamlessCompleted OnSeamlessCompleted;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void CreateMainWidget();
};
