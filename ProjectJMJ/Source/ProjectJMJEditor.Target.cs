// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using static UnrealBuildTool.ModuleRules;

public class ProjectJMJEditorTarget : TargetRules
{
	public ProjectJMJEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("ProjectJMJ");

		if (Configuration == UnrealTargetConfiguration.Debug || Configuration == UnrealTargetConfiguration.DebugGame)
		{
            //bUseGameplayDebuggerCore = true;
            //bAdaptiveUnityDisablesOptimizations = true;
            bUseInlining = false;
            bUseUnityBuild = false;
            bUsePCHFiles = false;
            BuildEnvironment = TargetBuildEnvironment.Unique;
            //OptimizeCode = CodeOptimization.Never; // 禁用优化
            AdditionalCompilerArguments = "/Od"; // 禁用优化
        }

    }
}
