#include "HorizonVehicle.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/StaticMesh.h"
#include "InputCoreTypes.h"

AHorizonVehicle::AHorizonVehicle()
{
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
    VehicleBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleBody"));
    SetRootComponent(VehicleBody);
    if (CubeMesh.Succeeded()) VehicleBody->SetStaticMesh(CubeMesh.Object);
    VehicleBody->SetRelativeScale3D(FVector(2.15f, 4.5f, 0.75f));
    VehicleBody->SetCollisionProfileName(TEXT("BlockAll"));
    ApplyTint(VehicleBody, FLinearColor(0.018f, 0.055f, 0.11f));
    UStaticMeshComponent* Cabin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cabin"));
    Cabin->SetupAttachment(VehicleBody);
    if (CubeMesh.Succeeded()) Cabin->SetStaticMesh(CubeMesh.Object);
    Cabin->SetRelativeLocation(FVector(0.f, -0.15f, 0.72f));
    Cabin->SetRelativeScale3D(FVector(1.55f, 2.2f, 0.72f));
    Cabin->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ApplyTint(Cabin, FLinearColor(0.045f, 0.18f, 0.25f));
    const FVector WheelPositions[] = {
        FVector(-1.05f, 1.35f, -0.18f), FVector(1.05f, 1.35f, -0.18f),
        FVector(-1.05f, -1.35f, -0.18f), FVector(1.05f, -1.35f, -0.18f)
    };
    for (int32 Index = 0; Index < 4; ++Index)
    {
        UStaticMeshComponent* Wheel = CreateDefaultSubobject<UStaticMeshComponent>(*FString::Printf(TEXT("Wheel_%d"), Index));
        Wheel->SetupAttachment(VehicleBody);
        if (CylinderMesh.Succeeded()) Wheel->SetStaticMesh(CylinderMesh.Object);
        Wheel->SetRelativeLocation(WheelPositions[Index]);
        Wheel->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
        Wheel->SetRelativeScale3D(FVector(0.43f, 0.20f, 0.43f));
        Wheel->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        ApplyTint(Wheel, FLinearColor(0.008f, 0.01f, 0.015f));
        Wheels.Add(Wheel);
    }
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("VehicleCameraBoom"));
    CameraBoom->SetupAttachment(VehicleBody);
    CameraBoom->TargetArmLength = 720.f;
    CameraBoom->SocketOffset = FVector(0.f, 0.f, 180.f);
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 5.f;
    VehicleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VehicleCamera"));
    VehicleCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    VehicleCamera->bUsePawnControlRotation = false;
    AutoPossessPlayer = EAutoReceiveInput::Disabled;
}
void AHorizonVehicle::ApplyTint(UStaticMeshComponent* Component, const FLinearColor& Color)
{
    if (!Component) return;
    if (UMaterialInstanceDynamic* MID = Component->CreateAndSetMaterialInstanceDynamic(0))
    {
        MID->SetVectorParameterValue(TEXT("BaseColor"), Color);
        MID->SetVectorParameterValue(TEXT("Color"), Color);
    }
}
void AHorizonVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AHorizonVehicle::SetThrottle);
    PlayerInputComponent->BindAxis("MoveRight", this, &AHorizonVehicle::SetSteering);
    PlayerInputComponent->BindAxis("Brake", this, &AHorizonVehicle::SetBrake);
}
void AHorizonVehicle::SetThrottle(float Value) { Throttle = FMath::Clamp(Value, -1.f, 1.f); }
void AHorizonVehicle::SetSteering(float Value) { Steering = FMath::Clamp(Value, -1.f, 1.f); }
void AHorizonVehicle::SetBrake(float Value) { BrakeAmount = FMath::Clamp(Value, 0.f, 1.f); }
void AHorizonVehicle::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    const float DesiredSpeed = Throttle * MaxSpeed * (1.f - BrakeAmount);
    CurrentSpeed = FMath::FInterpTo(CurrentSpeed, DesiredSpeed, DeltaSeconds, BrakeAmount > 0.f ? 7.f : 2.2f);
    const float SpeedRatio = FMath::Clamp(FMath::Abs(CurrentSpeed) / MaxSpeed, 0.15f, 1.f);
    AddActorWorldRotation(FRotator(0.f, Steering * 82.f * SpeedRatio * DeltaSeconds, 0.f));
    AddActorWorldOffset(GetActorForwardVector() * CurrentSpeed * DeltaSeconds, true);
    for (UStaticMeshComponent* Wheel : Wheels)
        if (Wheel) Wheel->AddLocalRotation(FRotator(0.f, CurrentSpeed * DeltaSeconds * 0.08f, 0.f));
}
