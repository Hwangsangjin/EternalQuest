// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Component/EQComponentBase.h"
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
	bool AddToInventory(const FEQSlot& InSlot);
	void DropItem(FEQSlot* InSlot);

	UFUNCTION(Server, Reliable)
	void ServerRPC_DropItem(const FName& RowName,const EEQItemType& ItemType,const int32& Quantity, const FTransform& ItemLoc);

	UFUNCTION(Client, Reliable)
	void ClientRPC_DropItem(const FName& RowName,const EEQItemType& ItemType,const int32& Quantity);
	
	// ----- 함수 -----

	// ----- 구충돌 변수 -----
	FVector StartVec, EndVec;
	FHitResult HitInfo;
	
	UPROPERTY()
	TArray<AActor*> ArrActor;
	
	UPROPERTY(Replicated)
	AEQItemBase* CurrItem;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// ----- 구충돌 변수 -----

	// ----- 변수 -----
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UDataTable> ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEQAllItem EQAllItem;
	
	UPROPERTY()
	FEQSlot EmptySlot;

	UPROPERTY()
	AEQCharacterPlayer* MyPlayer;

	UPROPERTY()
	TSubclassOf<AEQItemBase> ItemFactory;
	
	UPROPERTY()
	FName DropRowName;

	UPROPERTY()
	TEnumAsByte<EEQItemType> DropItemType;

	UPROPERTY()
	int32 DropQuantity;
	// ----- 변수 -----
};
