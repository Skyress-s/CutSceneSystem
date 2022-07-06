// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CutSceneSystem : ModuleRules
{
	public CutSceneSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "LevelSequence", "MovieScene", "UMG" });
	}
}
