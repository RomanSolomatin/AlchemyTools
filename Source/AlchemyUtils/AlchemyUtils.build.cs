// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class AlchemyUtils : ModuleRules
{
    public AlchemyUtils(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] {});

		PrivateIncludePaths.AddRange(new string[] {
			"AlchemyUtils/Public",
			"AlchemyUtils/Private"
		});
	}
}
