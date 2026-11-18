using UnrealBuildTool;
using System.Collections.Generic;
public class GTAHorizonEditorTarget : TargetRules
{
    public GTAHorizonEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
        ExtraModuleNames.Add("GTAHorizon");
    }
}
