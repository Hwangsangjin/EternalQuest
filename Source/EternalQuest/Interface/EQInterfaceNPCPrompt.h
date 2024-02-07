// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EQInterfaceNPCPrompt.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEQInterfaceNPCPrompt : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ETERNALQUEST_API IEQInterfaceNPCPrompt
{
	GENERATED_BODY()

public:

	virtual void PlayPrompt() = 0;
};
