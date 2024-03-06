// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Game/EQGameInstance.h"
#include "EQPlayerState.generated.h"

UCLASS()
class ETERNALQUEST_API AEQPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;

// User Name
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetUserName() { return UserName; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetUserName(FString NewUserName) { UserName = NewUserName; }
	void UpdateUserName();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	FString UserName;

// Class Type
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EClassType GetClassType() { return ClassType; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetClassType(EClassType NewClassType) { ClassType = NewClassType; }
	void UpdateClassType();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	EClassType ClassType = EClassType::ECT_None;
};
