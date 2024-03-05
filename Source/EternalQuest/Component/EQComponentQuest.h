// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentBase.h"
#include "EQComponentQuest.generated.h"

USTRUCT(BlueprintType, Atomic)
struct FEQQuestProgress : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<uint8> QuestStateArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bQuestCond1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bQuestCond2 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bQuestCond3 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 bQuestCond3Quantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bQuestCond4 = false;

};

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALQUEST_API UEQComponentQuest : public UEQComponentBase
{
	GENERATED_BODY()

	UEQComponentQuest();
public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InspectingItem();

	UPROPERTY()
	FEQQuestProgress QuestCondition;
};
