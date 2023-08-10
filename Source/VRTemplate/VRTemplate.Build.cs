// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class VRTemplate : ModuleRules
{
	public VRTemplate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "GameFeatures", "UMG" });

        PrivateDependencyModuleNames.AddRange(
            new string[] {                
                "LoadingScreen",
                "Slate",
                "SlateCore",
                "MoviePlayer",
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",
                "AIModule"
            }
        );
    }
}
