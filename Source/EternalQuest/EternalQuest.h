// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define NETMODEINFO_LOG ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("Client%d"), GPlayInEditorID) : ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("Standalone") : TEXT("Server")))
#define CALLINFO_LOG ANSI_TO_TCHAR(__FUNCTION__)
#define EQ_LOG(LogCategory, Verbosity, Format, ...) UE_LOG(LogCategory, Verbosity, TEXT("[%s] %s %s"), NETMODEINFO_LOG, CALLINFO_LOG, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogEternalQuest, Log, All);