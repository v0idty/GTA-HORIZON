# GTA HORIZON — Unreal Engine 5.8

**A City Without Limits.** An original mobile open-world prototype using Unreal Engine 5.8 and C++.

This is an independent fan-made project. It is not affiliated with Rockstar Games and does not include GTA source code, maps, characters, music, or proprietary assets.

## Current C++ prototype
- UE 5.8 project descriptor and game/editor targets.
- Third-person character movement and follow camera.
- Basic arcade-style vehicle pawn with enter/exit possession.
- Procedurally generated coastal-city graybox.
- Native C++ main menu and touch HUD.
- Android ARM64 package configuration.
- GitHub Actions workflow for a preconfigured Unreal build runner.

## Open in Unreal Engine
Install Unreal Engine 5.8 and the Android toolchain on a supported Windows development machine, then open GTAHorizon.uproject. Compile the GTAHorizon module when prompted.

## Android toolchain
Epic's UE 5.8 Android documentation lists Android SDK 35, NDK r27c, and JDK 21 as the relevant current toolchain versions. Use Turnkey or Epic's documented setup process to install the matching versions.

## GitHub Actions build
Workflow: .github/workflows/build-android.yml

Important: GitHub-hosted runners do not ship with Unreal Engine. This workflow deliberately targets a self-hosted Windows runner with:
- Unreal Engine 5.8 installed and licensed.
- Visual Studio 2022 C++ game-development tools.
- Android SDK 35, NDK r27c, OpenJDK 21.
- Runner labels ue-5.8 and android.
- UE_ROOT environment variable pointing to the UE installation.
- ANDROID_HOME or ANDROID_SDK_ROOT configured.

See Docs/BUILD-ANDROID.md. Without this runner, the APK job cannot run; repository files alone cannot compile Unreal Engine.

## Prototype limits
This is an early graybox foundation, not an AAA game and not a GTA 6 port. The city uses engine primitive meshes. Production assets, vehicle physics tuning, animation, traffic AI, pedestrian AI, missions, save data, weather, audio, and real-device profiling remain future milestones.

C++ is the main gameplay language. We will add native performance work only when profiling proves it is needed.
