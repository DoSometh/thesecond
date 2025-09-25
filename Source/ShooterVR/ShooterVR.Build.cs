// Copyright (C) RenZhai.2025.All Rights Reserved.
//As https://www.aboutcg.org/courseDetails/1639/introduce
//Game Demo:https://renzhai.net/781.html
//Ins:https://www.bilibili.com/video/BV11yezzsEAi/?spm_id_from=333.1387.homepage.video_card.click

using UnrealBuildTool;

public class ShooterVR : ModuleRules
{
	public ShooterVR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore",
			"SimpleModularGameplay",
			"HeadMountedDisplay",
			"NavigationSystem",
			"SimpleVRFeatureKit",
			"SimpleCombat",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			"SimpleGameplayAbilitiesExtend",
			"EnhancedInput",
			"DataRegistry",
			"Niagara",
		  //"SimpleThread",
			"SimpleRuntimeGamePrinting",
			"ChaosVehicles",
			"Json",
            "XRBase",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Slate",
			"SlateCore",
			"UMG"
		});
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
