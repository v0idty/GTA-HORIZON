#if UNITY_EDITOR
using System.IO;
using UnityEditor;
using UnityEditor.Build.Reporting;
using UnityEngine;

namespace GTAHorizon
{
    public static class EditorBuild
    {
        private const string ScenePath="Assets/Scenes/Boot.unity";

        [MenuItem("GTA HORIZON/Build Android APK")]
        public static void BuildAndroid()
        {
            Directory.CreateDirectory("Assets/Scenes");
            Directory.CreateDirectory("build/android");
            if(!File.Exists(ScenePath))
            {
                var scene=UnityEditor.SceneManagement.EditorSceneManager.NewScene(UnityEditor.SceneManagement.NewSceneSetup.EmptyScene);
                UnityEditor.SceneManagement.EditorSceneManager.SaveScene(scene,ScenePath);
            }
            EditorBuildSettings.scenes=new[]{new EditorBuildSettingsScene(ScenePath,true)};
            EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Android,BuildTarget.Android);
            PlayerSettings.companyName="v0idty studio";
            PlayerSettings.productName="GTA HORIZON";
            PlayerSettings.applicationIdentifier="com.v0idty.gtahorizon";
            PlayerSettings.bundleVersion="0.1.0";
            PlayerSettings.Android.bundleVersionCode=1;
            PlayerSettings.Android.targetArchitectures=AndroidArchitecture.ARM64;
            PlayerSettings.SetScriptingBackend(BuildTargetGroup.Android,ScriptingImplementation.IL2CPP);
            PlayerSettings.defaultInterfaceOrientation=UIOrientation.LandscapeLeft;
            var report=BuildPipeline.BuildPlayer(new BuildPlayerOptions{
                scenes=new[]{ScenePath},locationPathName="build/android/GTA-HORIZON.apk",
                target=BuildTarget.Android,options=BuildOptions.None});
            if(report.summary.result!=BuildResult.Succeeded)
                throw new System.Exception("Android build failed: "+report.summary.result);
        }
    }
}
#endif
