// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AlchemyIO : ModuleRules
{
	public AlchemyIO(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore",
            "ImageWrapper",
        });
		PrivateDependencyModuleNames.AddRange(new string[] { });

        PrivateIncludePaths.AddRange(new string[] {
            "AlchemyIO/Public",
            "AlchemyIO/Private"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }
	}
}
