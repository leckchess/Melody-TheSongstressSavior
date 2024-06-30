// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class TheSongstressSaviorTarget : TargetRules
{
	public TheSongstressSaviorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		MacPlatform.bUseDSYMFiles = false;

		ExtraModuleNames.AddRange( new string[] { "TheSongstressSavior" } );
	}
}
