// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct/EQStructEnumBase.h"
#include "EQItemBase.generated.h"


struct FEQSlot;

UCLASS()
class ETERNALQUEST_API AEQItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEQItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// ----- 함수 -----
	void SetItemName(const FName& InName, EEQItemType InType, const int32& InQuantity = 1);
	// ----- 함수 -----

	// ----- 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MySettings)
	UStaticMeshComponent* MeshComp;

	FEQSlot Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MySettings)
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Item")
	FDataTableRowHandle ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Item")
	TEnumAsByte<EEQItemType> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Item")
	int32 ItemQuantity;
	// ----- 변수 -----
};