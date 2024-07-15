// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "EQStructEnumBase.generated.h"

UCLASS()
class ETERNALQUEST_API AEQStructEnumBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEQStructEnumBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};


UENUM(BlueprintType)
enum EEQItemType
{
	Equipment,
	Consumtion,
	Material,
	Questitem,
	EquippingWeapon,
	EquippingShield
};


USTRUCT(BlueprintType, Atomic)
struct FEQItem : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Healing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float INT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Grade;
};

USTRUCT(BlueprintType, Atomic)
struct FEQSlot : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EEQItemType> ItemType = EEQItemType::Equipment;
};

USTRUCT(BlueprintType, Atomic)
struct FEQAllItem : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEQSlot> Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEQSlot> Consumtion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEQSlot> Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEQSlot> QuestItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEQSlot> EquippingSword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEQSlot> EquippingShield;

	FORCEINLINE bool IsEmpty()
	{
		if (EquippingSword.IsEmpty()) return true;
		if (EquippingShield.IsEmpty()) return true;
		
		for (int i = 0; i < 20; i++)
		{
			if (Equipment.IsEmpty()) return true;
			if (Consumtion.IsEmpty()) return true;
			if (Material.IsEmpty()) return true;
			if (QuestItem.IsEmpty()) return true;
		}
		return false;
	}
};

