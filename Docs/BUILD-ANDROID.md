# Android build for GTA HORIZON on Unreal Engine 5.8

## Required build machine
A standard GitHub-hosted runner does not include Unreal Engine. The workflow uses a self-hosted Windows runner with an installed and licensed Unreal Engine 5.8 toolchain.

Install and configure:
- Unreal Engine 5.8 (Epic Games Launcher installation or approved source build)
- Visual Studio 2022 with C++ game development tools
- UE 5.8-compatible Android Studio toolchain
- Android SDK 35, NDK r27c, OpenJDK 21
- GitHub Actions self-hosted runner with labels: ue-5.8 and android
- Environment variable UE_ROOT pointing to the UE 5.8 root
- ANDROID_HOME or ANDROID_SDK_ROOT set on the runner

Epic's UE 5.8 Android documentation lists the relevant SDK, NDK and JDK requirements.

## Run a build
1. Register and start the self-hosted runner on a Windows PC with the toolchain above.
2. In GitHub, open Actions → GTA HORIZON - Unreal Engine 5.8 Android.
3. Select Run workflow.
4. Download the GTA-HORIZON-UE5.8-Android-0.1 artifact when the job completes.

## Phone-only limitation
The repository can be edited from a phone, but an Android phone cannot host the required Windows Unreal Engine build runner. Without access to a compatible runner or an external Unreal build service, the APK build remains unavailable. Do not add engine credentials or account passwords to this repository.

## Prototype scope
The initial source includes C++ module targets, third-person character movement, an arcade vehicle pawn, a procedural city blockout, a main menu, touch HUD, and Android packaging settings. This is a graybox prototype, not a finished AAA game. It does not yet include production 3D assets, a finished map, missions, advanced NPC AI, or advanced mobile graphics assets.
