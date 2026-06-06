using UnrealBuildTool;
using System.Collections.Generic;

public class SwisstrainEditorTarget : TargetRules
{
    public SwisstrainEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.AddRange(new string[] { "Swisstrain" });
    }
}
