// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class newbie : ModuleRules
{
	public newbie(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
