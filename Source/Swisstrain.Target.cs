using UnrealBuildTool;
using System.Collections.Generic;

public class SwisstrainTarget : TargetRules
{
    public SwisstrainTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange(new string[] { "Swisstrain" });
    }
}
