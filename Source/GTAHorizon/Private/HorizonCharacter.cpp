#include "HorizonCharacter.h"
#include "HorizonPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

AHorizonCharacter::AHorizonCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshAsset(TEXT("/Engine/BasicShapes/Capsule.Capsule"));
    BodyVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyVisual"));
    BodyVisual->SetupAttachment(RootComponent);
    if (BodyMeshAsset.Succeeded()) BodyVisual->SetStaticMesh(BodyMeshAsset.Object);
    BodyVisual->SetRelativeLocation(FVector(0.f,0.f,-5.f));
    BodyVisual->SetRelativeScale3D(FVector(.72f,.72f,.95f));
    BodyVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    if (UMaterialInstanceDynamic* MID = BodyVisual->CreateAndSetMaterialInstanceDynamic(0))
    {
        MID->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(.08f,.45f,.72f));
        MID->SetVectorParameterValue(TEXT("Color"), FLinearColor(.08f,.45f,.72f));
    }

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 430.f;
    CameraBoom->SocketOffset = FVector(0.f, 55.f, 70.f);
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 9.f;
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 560.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 520.f;
    GetCharacterMovement()->MaxWalkSpeedCrouched = 180.f;
    GetCharacterMovement()->JumpZVelocity = 480.f;
    GetCharacterMovement()->AirControl = 0.30f;
}
void AHorizonCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (!TouchMove.IsNearlyZero())
    {
        AddMovementInput(GetActorForwardVector(), TouchMove.Y);
        AddMovementInput(GetActorRightVector(), TouchMove.X);
    }
}
void AHorizonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AHorizonCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AHorizonCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AHorizonCharacter::TurnCamera);
    PlayerInputComponent->BindAxis("LookUp", this, &AHorizonCharacter::LookCamera);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction("VehicleInteract", IE_Pressed, this, &AHorizonCharacter::InteractWithVehicle);
}
void AHorizonCharacter::MoveForward(float Value)
{
    if (!Controller || FMath::IsNearlyZero(Value)) return;
    const FRotator Yaw(0.f, Controller->GetControlRotation().Yaw, 0.f);
    AddMovementInput(FRotationMatrix(Yaw).GetUnitAxis(EAxis::X), Value);
}
void AHorizonCharacter::MoveRight(float Value)
{
    if (!Controller || FMath::IsNearlyZero(Value)) return;
    const FRotator Yaw(0.f, Controller->GetControlRotation().Yaw, 0.f);
    AddMovementInput(FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y), Value);
}
void AHorizonCharacter::TurnCamera(float Value) { AddControllerYawInput(Value); }
void AHorizonCharacter::LookCamera(float Value) { AddControllerPitchInput(Value); }
void AHorizonCharacter::SetTouchMove(FVector2D Value) { TouchMove = Value.GetClampedToMaxSize(1.f); }
void AHorizonCharacter::InteractWithVehicle()
{
    if (AHorizonPlayerController* PC = Cast<AHorizonPlayerController>(GetController())) PC->ToggleVehicle();
}
