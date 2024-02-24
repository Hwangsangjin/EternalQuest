// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EQWidgetChattingSystem.generated.h"

class UEQWidgetChatMessage;
class UEditableText;
class UScrollBox;
/**
 * 
 */
UCLASS()
class ETERNALQUEST_API UEQWidgetChattingSystem : public UUserWidget
{
	GENERATED_BODY()

public:
	UEQWidgetChattingSystem(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnTextCommittedChat(const FText& Text, ETextCommit::Type CommitMethod);

	void UpdateChat(const FText& InText, const FText& InPlayerName);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UScrollBox> ScrBox_ChatList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UEditableText> EditText_ChatInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEQWidgetChatMessage> ChatMessageFactory;
};
