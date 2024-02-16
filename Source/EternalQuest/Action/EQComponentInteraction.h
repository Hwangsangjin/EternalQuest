// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Action/EQComponentBase.h"
#include "EQComponentInteraction.generated.h"

class UEQComponentInventory;
struct FEQSlot;
class AEQItemBase;
class UEQWidgetNpcPrompt;
class AEQCharacterNeutralPlayer;
class UBoxComponent;

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALQUEST_API UEQComponentInteraction : public UEQComponentBase
{
	GENERATED_BODY()
public:
	UEQComponentInteraction();
	// ----- Override 함수 -----
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;
	virtual void SetupPlayerInput(UInputComponent* PlayerInputComponent) override;
	// ----- Override 함수 -----

	// ----- 함수 -----
	void Interaction();
	void EatItem();
	bool AddToInventory(const FEQSlot& InSlot);
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	// ----- 함수 -----

	// ----- 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> EatItemAction;

	UPROPERTY()
	TObjectPtr<AEQCharacterNeutralPlayer> NPC;
	
	UPROPERTY()
	TObjectPtr<AEQItemBase> Item;

	UPROPERTY()
	TSubclassOf<UUserWidget> PromptWidgetFactory;

	UPROPERTY()
	TObjectPtr<UEQWidgetNpcPrompt> PromptWidget;

	UPROPERTY()
	TObjectPtr<UEQComponentInventory> EQComponentInventory;
	// ----- 변수 -----
};
