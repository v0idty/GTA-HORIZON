#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HorizonVehicle.generated.h"
class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class GTAHORIZON_API AHorizonVehicle : public APawn
{
    GENERATED_BODY()
public:
    AHorizonVehicle();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    UStaticMeshComponent* GetVehicleBody() const { return VehicleBody; }
    void SetTouchControls(float InThrottle, float InSteering, float InBrake);
private:
    void SetThrottle(float Value);
    void SetSteering(float Value);
    void SetBrake(float Value);
    void ApplyTint(UStaticMeshComponent* Component, const FLinearColor& Color);
    UPROPERTY(VisibleAnywhere) TObjectPtr<UBoxComponent> CollisionRoot;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> VehicleBody;
    UPROPERTY(VisibleAnywhere) TObjectPtr<USpringArmComponent> CameraBoom;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UCameraComponent> VehicleCamera;
    UPROPERTY() TArray<TObjectPtr<UStaticMeshComponent>> Wheels;
    float Throttle=0.f;
    float Steering=0.f;
    float CurrentSpeed=0.f;
    float MaxSpeed=2600.f;
    float BrakeAmount=0.f;
};
