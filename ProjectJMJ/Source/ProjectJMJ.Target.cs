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


        // �����Ż��Ա����
        if (Configuration == UnrealTargetConfiguration.Debug || Configuration == UnrealTargetConfiguration.DebugGame)
        {
            //bUseInlining = false;
            //bUseUnityBuild = false;
            //bUsePCHFiles = false;
            //bForceEnableExceptions = true;

            // ȫ�ֽ����Ż�
            //OptimizeCode = CodeOptimization.Never;

            

            //EnableOptimizeCodeForModules

            // ���ȫ�ֱ���������
            //PublicDefinitions.Add("NO_OPTIMIZATION");

            // ����Զ�����������ֱ�Ӵ��ݸ���������
            //AdditionalCompilerArguments = "/Od"; // �����Ż�
        }

        //PublicDefinitions.Add("UE_BUILD_DEBUG=1"); // �Զ�����Ժ�
        //if (Target.Configuration == UnrealTargetConfiguration.Debug)
        //{
        //    Target.bUseFastPDBLinking = true; // �ӿ���Է�������
        //    Target.bDebugBuildsActuallyUseDebugCRT = true; // ǿ��ʹ��Debug CRT
        //    Target.GlobalCompileArguments.Add("/Od"); // �����Ż�
        //}

    }
}
