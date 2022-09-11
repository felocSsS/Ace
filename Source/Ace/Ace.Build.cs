// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ace : ModuleRules
{
	public Ace(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		MinFilesUsingPrecompiledHeaderOverride = 1;
		bUseUnity = false;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG", 
			"SlateCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});

		PublicIncludePaths.AddRange(new string[]
		{
			"Ace"
		});
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
