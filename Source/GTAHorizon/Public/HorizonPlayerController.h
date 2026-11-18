#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HorizonPlayerController.generated.h"
class UHorizonMenuWidget;
class UHorizonHUDWidget;
class AHorizonCharacter;
UCLASS()
class GTAHORIZON_API AHorizonPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    void ToggleVehicle();
    void StartFreeRoam();
private:
    UFUNCTION() void HandleStartRequested();
    UPROPERTY() TObjectPtr<UHorizonMenuWidget> MenuWidget;
    UPROPERTY() TObjectPtr<UHorizonHUDWidget> HUDWidget;
    UPROPERTY() TObjectPtr<AHorizonCharacter> StoredCharacter;
    bool bInFreeRoam = false;
};
