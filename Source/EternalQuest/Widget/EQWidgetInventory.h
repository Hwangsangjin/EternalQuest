// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/EQComponentInventory.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"
#include "EQWidgetInventory.generated.h"

class UEQWidgetItemDropArea;
class UEQWidgetItemInfo;
class UEQWidgetItemSlot;
class UEQComponentInventory;
class UWrapBox;
class UWidgetSwitcher;
class UButton;
class USizeBox;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetInventory : public UUserWidget
{
	GENERATED_BODY()

	UEQWidgetInventory(const FObjectInitializer &ObjectInitializer);
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	// ----- 함수 -----
	void OpenCloseInventoryWidget();
	void UpdateItemInInventoryUI();
	void ClearItemInventory();
	void AddItemInventory();

	UFUNCTION()
	void OnClickBtnEquip();

	UFUNCTION()
	void OnClickBtnConsume();

	UFUNCTION()
	void OnClickBtnMaterial();

	UFUNCTION()
	void OnClickBtnQuestItem();
	// ----- 함수 -----

	// ----- 변수 -----
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Base;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Equip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Consume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_Material;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButton> Btn_QuestItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWidgetSwitcher> WS_Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWrapBox> WrapBox_Equip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWrapBox> WrapBox_Equipping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWrapBox> WrapBox_Consume;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWrapBox> WrapBox_Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWrapBox> WrapBox_QuestItem;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEQWidgetItemInfo> WBP_EQWidgetItemInfo;
	
	bool bVisibilityFlag = false;

	UPROPERTY()
	TObjectPtr<UEQComponentInventory> EQComponentInventory;

	UPROPERTY()
	TObjectPtr<AEQCharacterPlayer> Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ABCSettings)
	TSubclassOf<UUserWidget> ItemSlotFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundWave> OpenInventorySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundWave> UIBaseSound;
	// ----- 변수 -----

};
