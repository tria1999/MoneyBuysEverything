// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MoneyBuysEverything : ModuleRules
{
	public MoneyBuysEverything(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "UMG", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
    }
}
