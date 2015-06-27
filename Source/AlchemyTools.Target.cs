//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

using UnrealBuildTool;
using System.Collections.Generic;

public class AlchemyToolsTarget : TargetRules
{
	public AlchemyToolsTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { 
		"AlchemyTools", 
		"AlchemyCamera", 
		"AlchemyIO", 
		"AlchemySideScroller" } );
	}
}
