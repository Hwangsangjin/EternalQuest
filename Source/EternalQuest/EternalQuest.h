// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOCALROLEINFO_LOG *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetLocalRole()))
#define REMOTEROLEINFO_LOG *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetRemoteRole()))
#define SUBLOCALROLEINFO_LOG *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetLocalRole()))
#define SUBREMOTEROLEINFO_LOG *(UEnum::GetValueAsString(TEXT("Engine.ENetRole"), GetOwner()->GetRemoteRole()))
#define NETMODEINFO_LOG ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) : ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER")))
#define CALLINFO_LOG ANSI_TO_TCHAR(__FUNCTION__)

#define EQ_LOG(LogCategory, Verbosity, Format, ...) UE_LOG(LogCategory, Verbosity, TEXT("[%s][%s/%s] %s %s"), NETMODEINFO_LOG, LOCALROLEINFO_LOG, REMOTEROLEINFO_LOG, CALLINFO_LOG, *FString::Printf(Format, ##__VA_ARGS__))
#define EQ_SUBLOG(LogCategory, Verbosity, Format, ...) UE_LOG(LogCategory, Verbosity, TEXT("[%s][%s/%s] %s %s"), NETMODEINFO_LOG, SUBLOCALROLEINFO_LOG, SUBREMOTEROLEINFO_LOG, CALLINFO_LOG, *FString::Printf(Format, ##__VA_ARGS__))

DECLARE_LOG_CATEGORY_EXTERN(LogEternalQuest, Log, All);