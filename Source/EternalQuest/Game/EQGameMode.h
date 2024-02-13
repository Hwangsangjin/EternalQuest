// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EQGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ETERNALQUEST_API AEQGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEQGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
