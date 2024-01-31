// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EternalQuest : ModuleRules
{
	public EternalQuest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
        PublicIncludePaths.AddRange(new string[] { "EternalQuest" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Niagara", "NavigationSystem", "AIModule", "GameplayTasks", "OnlineSubsystem", "OnlineSubsystemSteam" });
	}
}
