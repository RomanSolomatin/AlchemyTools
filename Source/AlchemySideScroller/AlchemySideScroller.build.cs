//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

using UnrealBuildTool;

public class AlchemySideScroller : ModuleRules
{
	public AlchemySideScroller(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });

        PrivateIncludePaths.AddRange(new string[] {
            "AlchemySideScroller/Public",
            "AlchemySideScroller/Private"
        });
	}
}
