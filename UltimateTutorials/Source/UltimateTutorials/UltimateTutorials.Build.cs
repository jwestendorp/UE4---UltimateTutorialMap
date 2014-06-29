// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UltimateTutorials : ModuleRules
{
	public UltimateTutorials(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		MinFilesUsingPrecompiledHeaderOverride = 1;
		bFasterWithoutUnity = true;
	}
}
