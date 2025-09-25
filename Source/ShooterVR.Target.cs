// Copyright (C) RenZhai.2025.All Rights Reserved.
//As£ºhttps://www.aboutcg.org/courseDetails/1639/introduce
//Game Demo:https://renzhai.net/781.html
//Ins:https://www.bilibili.com/video/BV11yezzsEAi/?spm_id_from=333.1387.homepage.video_card.click

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooterVRTarget : TargetRules
{
	public ShooterVRTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange( new string[] { "ShooterVR" } );
	}
}
