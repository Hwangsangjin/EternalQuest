// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct/EQStructEnumBase.h"
#include "EQItemBase.generated.h"


class UNiagaraSystem;
class UNiagaraComponent;
struct FEQSlot;

UCLASS()
class ETERNALQUEST_API AEQItemBase : public AActor
{
	GENERATED_BODY()
	
public:
	AEQItemBase();

protected:
	virtual void PostNetInit() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// ----- 함수 -----
	UFUNCTION()
	void SetItemName(const FName& InName, EEQItemType InType, const int32& InQuantity = 1);
	// ----- 함수 -----

	// ----- 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MySettings)
	UStaticMeshComponent* MeshComp;

	UPROPERTY()
	UStaticMesh* StaticMesh;

	UPROPERTY(Replicated)
	FEQSlot Slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MySettings)
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Item", Replicated)
	FDataTableRowHandle ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Item", Replicated)
	TEnumAsByte<EEQItemType> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Item", Replicated)
	int32 ItemQuantity;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraComponent> ItemVFX;

	UPROPERTY()
	TObjectPtr<UNiagaraSystem> CommonVFX;

	UPROPERTY()
	TObjectPtr<UNiagaraSystem> UnCommonVFX;

	UPROPERTY()
	TObjectPtr<UNiagaraSystem> EpicVFX;

	UPROPERTY()
	TObjectPtr<UNiagaraSystem> LegendaryVFX;
	// ----- 변수 -----
};