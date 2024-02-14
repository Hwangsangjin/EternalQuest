// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EQStructItem.generated.h"

/**
 * 
 */
class ETERNALQUEST_API EQStructItem
{
public:
	EQStructItem();
	~EQStructItem();
};

USTRUCT(Atomic, BlueprintType)
struct FItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Healing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float INT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LUK;
};

USTRUCT(BlueprintType)
struct FSlot
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
};
