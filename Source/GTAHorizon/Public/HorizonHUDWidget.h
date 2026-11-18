#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HorizonHUDWidget.generated.h"
UCLASS()
class GTAHORIZON_API UHorizonHUDWidget : public UUserWidget
{
    GENERATED_BODY()
protected:
    virtual void NativeConstruct() override;
private:
    bool bForward=false, bBack=false, bLeft=false, bRight=false, bBrake=false;
    void RefreshTouchInput();
    UFUNCTION() void ForwardPressed();
    UFUNCTION() void ForwardReleased();
    UFUNCTION() void BackPressed();
    UFUNCTION() void BackReleased();
    UFUNCTION() void LeftPressed();
    UFUNCTION() void LeftReleased();
    UFUNCTION() void RightPressed();
    UFUNCTION() void RightReleased();
    UFUNCTION() void BrakePressed();
    UFUNCTION() void BrakeReleased();
    UFUNCTION() void JumpClicked();
    UFUNCTION() void VehicleClicked();
};
