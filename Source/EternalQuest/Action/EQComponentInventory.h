// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Action/EQComponentBase.h"
#include "Struct/EQStructEnumBase.h"
#include "EQComponentInventory.generated.h"

class UEQWidgetInventory;
class AEQItemBase;
class UInputAction;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALQUEST_API UEQComponentInventory : public UEQComponentBase
{
	GENERATED_BODY()

public:
	UEQComponentInventory();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;

	// ----- 함수 -----
	// ----- 함수 -----

	// ----- 구충돌 변수 -----
	FVector StartVec, EndVec;
	FHitResult HitInfo;
	
	UPROPERTY()
	TArray<AActor*> ArrActor;
	
	UPROPERTY()
	TObjectPtr<AEQItemBase> CurrItem;
	// ----- 구충돌 변수 -----

	// ----- 변수 -----
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UDataTable> ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEQAllItem EQAllItem;

	UPROPERTY()
	FEQSlot EmptySlot;
	// ----- 변수 -----
};
