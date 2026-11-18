# GTA HORIZON — Version 0.1

**A City Without Limits.** An original mobile open-world prototype built with Unity 6 and C#.

This is an independent fan-made learning project. It is not affiliated with Rockstar Games and contains no GTA source code, maps, characters, music, or proprietary assets.

## Prototype features
- Runtime-generated coastal city blockout.
- Third-person player movement and follow camera.
- Enter/exit a simple drivable vehicle.
- Arcade vehicle movement.
- Android touch controls and keyboard fallback.
- Main menu and title screen.
- Android ARM64 build workflow.

## Toolchain
- Unity 6 (Editor version pinned in `ProjectSettings/ProjectVersion.txt`)
- Universal Render Pipeline (URP)
- C# gameplay
- Optional native C++ sample in `Native/Android`; it is not required by the game.

## Open in Unity
Install Unity Hub with the matching Unity Editor and Android Build Support (SDK, NDK, OpenJDK). Open this repository as a Unity project. The editor helper creates a boot scene and configures the mobile URP pipeline.

## GitHub Actions APK build
Workflow: `.github/workflows/build-android.yml`

Add these repository Actions secrets:
- `UNITY_LICENSE`: contents of your Unity license file.
- `UNITY_EMAIL`: Unity account email.
- `UNITY_PASSWORD`: only if required by your GameCI license activation method.

Never commit license credentials. Then run **Actions → GTA HORIZON - Android APK → Run workflow**. The APK is uploaded as the `GTA-HORIZON-Android-0.1` artifact.

## Controls
- WASD / arrow keys or on-screen controls: move / steer.
- E or ACTION: enter / exit nearby car.
- Space: brake while driving.

## Honest scope
This is a first playable foundation, not a GTA 6 port or AAA production. The initial city uses procedural primitives. High-detail original models, animation, audio, missions, save systems, advanced AI, and real-device profiling are future milestones. C++ is not inherently easier or faster than C#; use native code only for measured bottlenecks.
