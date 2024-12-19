// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using static UnrealBuildTool.ModuleRules;

public class ProjectJMJTarget : TargetRules
{
	public ProjectJMJTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("ProjectJMJ");


        // 禁用优化以便调试
        if (Configuration == UnrealTargetConfiguration.Debug || Configuration == UnrealTargetConfiguration.DebugGame)
        {
            //bUseInlining = false;
            //bUseUnityBuild = false;
            //bUsePCHFiles = false;
            //bForceEnableExceptions = true;

            // 全局禁用优化
            //OptimizeCode = CodeOptimization.Never;

            

            //EnableOptimizeCodeForModules

            // 添加全局编译器定义
            //PublicDefinitions.Add("NO_OPTIMIZATION");

            // 添加自定义编译参数（直接传递给编译器）
            //AdditionalCompilerArguments = "/Od"; // 禁用优化
        }

        //PublicDefinitions.Add("UE_BUILD_DEBUG=1"); // 自定义调试宏
        //if (Target.Configuration == UnrealTargetConfiguration.Debug)
        //{
        //    Target.bUseFastPDBLinking = true; // 加快调试符号生成
        //    Target.bDebugBuildsActuallyUseDebugCRT = true; // 强制使用Debug CRT
        //    Target.GlobalCompileArguments.Add("/Od"); // 禁用优化
        //}

    }
}
