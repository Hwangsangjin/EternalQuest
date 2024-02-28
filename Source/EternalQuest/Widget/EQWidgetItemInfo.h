// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/EQStructEnumBase.h"
#include "EQWidgetItemInfo.generated.h"

class AEQItemPreview;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetItemInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetItemInfo(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void UpdateItemInfo(const FEQSlot& InItem);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Img_RenderItem;

	UPROPERTY()
	TSubclassOf<AActor> ItemPreviewFactory;

	UPROPERTY()
	TObjectPtr<AEQItemPreview> ItemPreview;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_IncreaseHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_IncreaseMP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_IncreaseSTR;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_IncreaseINT;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> Txt_IncreaseDEF;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Img_HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Img_MP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Img_STR;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Img_INT;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> Img_DEF;

	
};
