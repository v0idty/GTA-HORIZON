#if UNITY_EDITOR
using System.IO;
using UnityEditor;
using UnityEditor.Build.Reporting;
using UnityEngine;
using UnityEngine.Rendering;
using UnityEngine.Rendering.Universal;

namespace GTAHorizon
{
    public static class EditorBuild
    {
        private const string ScenePath = "Assets/Scenes/Boot.unity";

        [MenuItem("GTA HORIZON/Configure URP Graphics")]
        public static void ConfigureGraphics()
        {
            EnsureUrp();
            Debug.Log("GTA HORIZON: mobile URP pipeline configured.");
        }

        [MenuItem("GTA HORIZON/Build Android APK")]
        public static void BuildAndroid()
        {
            EnsureUrp();
            Directory.CreateDirectory("Assets/Scenes");
            Directory.CreateDirectory("build/android");
            if (!File.Exists(ScenePath))
            {
                var scene = UnityEditor.SceneManagement.EditorSceneManager.NewScene(
                    UnityEditor.SceneManagement.NewSceneSetup.EmptyScene);
                UnityEditor.SceneManagement.EditorSceneManager.SaveScene(scene, ScenePath);
            }

            EditorBuildSettings.scenes = new[] { new EditorBuildSettingsScene(ScenePath, true) };
            EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Android, BuildTarget.Android);
            PlayerSettings.companyName = "v0idty studio";
            PlayerSettings.productName = "GTA HORIZON";
            PlayerSettings.applicationIdentifier = "com.v0idty.gtahorizon";
            PlayerSettings.bundleVersion = "0.1.0";
            PlayerSettings.Android.bundleVersionCode = 1;
            PlayerSettings.Android.minSdkVersion = AndroidSdkVersions.AndroidApiLevel26;
            PlayerSettings.Android.targetArchitectures = AndroidArchitecture.ARM64;
            PlayerSettings.SetScriptingBackend(BuildTargetGroup.Android, ScriptingImplementation.IL2CPP);
            PlayerSettings.defaultInterfaceOrientation = UIOrientation.LandscapeLeft;
            PlayerSettings.allowedAutorotateToLandscapeLeft = true;
            PlayerSettings.allowedAutorotateToLandscapeRight = true;

            var report = BuildPipeline.BuildPlayer(new BuildPlayerOptions {
                scenes = new[] { ScenePath },
                locationPathName = "build/android/GTA-HORIZON.apk",
                target = BuildTarget.Android,
                options = BuildOptions.None
            });
            if (report.summary.result != BuildResult.Succeeded)
                throw new System.Exception("Android build failed: " + report.summary.result +
                    " / " + report.summary.totalErrors + " errors.");
            Debug.Log("APK created: " + report.summary.outputPath);
        }

        private static void EnsureUrp()
        {
            const string folder = "Assets/Settings";
            const string rendererPath = folder + "/HorizonRenderer.asset";
            const string pipelinePath = folder + "/HorizonMobileURP.asset";
            if (!AssetDatabase.IsValidFolder(folder)) AssetDatabase.CreateFolder("Assets", "Settings");

            var pipeline = AssetDatabase.LoadAssetAtPath<UniversalRenderPipelineAsset>(pipelinePath);
            if (pipeline == null)
            {
                var renderer = AssetDatabase.LoadAssetAtPath<UniversalRendererData>(rendererPath);
                if (renderer == null)
                {
                    renderer = ScriptableObject.CreateInstance<UniversalRendererData>();
                    renderer.name = "Horizon Mobile Renderer";
                    AssetDatabase.CreateAsset(renderer, rendererPath);
                }
                pipeline = UniversalRenderPipelineAsset.Create(renderer);
                pipeline.name = "Horizon Mobile URP";
                AssetDatabase.CreateAsset(pipeline, pipelinePath);
            }
            GraphicsSettings.defaultRenderPipeline = pipeline;
            QualitySettings.renderPipeline = pipeline;
            AssetDatabase.SaveAssets();
            AssetDatabase.Refresh();
        }
    }
}
#endif
