#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HorizonCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
UCLASS()
class GTAHORIZON_API AHorizonCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    AHorizonCharacter();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    void SetTouchMove(FVector2D Value);
    void InteractWithVehicle();
protected:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void TurnCamera(float Value);
    void LookCamera(float Value);
private:
    UPROPERTY(VisibleAnywhere, Category="Camera") TObjectPtr<USpringArmComponent> CameraBoom;
    UPROPERTY(VisibleAnywhere, Category="Camera") TObjectPtr<UCameraComponent> FollowCamera;
    UPROPERTY(VisibleAnywhere, Category="Visual") TObjectPtr<UStaticMeshComponent> BodyVisual;
    FVector2D TouchMove = FVector2D::ZeroVector;
};
