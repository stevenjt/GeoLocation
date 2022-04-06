/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
 **/

using System.IO;
using UnrealBuildTool;

public class GeoLocation : ModuleRules
{
#if WITH_FORWARDED_MODULE_RULES_CTOR
    public GeoLocation(ReadOnlyTargetRules Target) : base(Target)
#else
    public GeoLocation(TargetInfo Target)
#endif
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
            {
                "Runtime/Core/Public/Misc",
                "Runtime/Core/Public/Math",
                "Runtime/Engine/Public",
                "Runtime/Engine/Classes/Engine",
                "Runtime/Engine/Classes/GameFramework",
                "Runtime/Launch",
                "Runtime/Launch/Public"
            }
        );

        PrivateIncludePaths.AddRange(new string[]
            {
                "GeoLocation/Private"
            }
        );

        PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core"
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
            }
        );

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.Add("AndroidPermission");

            #if WITH_FORWARDED_MODULE_RULES_CTOR
                string GeoLocationPluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            #else
                string GeoLocationPluginPath = Utils.MakePathRelativeTo(ModuleDirectory, BuildConfiguration.RelativeEnginePath);
#endif

            #if UE_4_19_OR_LATER
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(GeoLocationPluginPath, "GeoLocation_APL.xml"));   
            #else
                AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(GeoLocationPluginPath, "GeoLocation_APL.xml")));
            #endif
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicFrameworks.Add("CoreLocation");
        }
    }
}
