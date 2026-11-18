#include "HorizonPlayerController.h"
#include "HorizonMenuWidget.h"
#include "HorizonHUDWidget.h"
#include "HorizonCharacter.h"
#include "HorizonVehicle.h"
#include "Blueprint/UserWidget.h"
#include "EngineUtils.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/SWidget.h"

void AHorizonPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (IsLocalController())
    {
        MenuWidget = CreateWidget<UHorizonMenuWidget>(this, UHorizonMenuWidget::StaticClass());
        if (MenuWidget)
        {
            MenuWidget->OnStartRequested.AddDynamic(this,&AHorizonPlayerController::HandleStartRequested);
            MenuWidget->AddToViewport(10);
        }
        SetShowMouseCursor(true);
        FInputModeUIOnly Mode;
        if (MenuWidget) Mode.SetWidgetToFocus(MenuWidget->TakeWidget());
        SetInputMode(Mode);
    }
}
void AHorizonPlayerController::HandleStartRequested(){StartFreeRoam();}
void AHorizonPlayerController::StartFreeRoam()
{
    if (bInFreeRoam) return;
    bInFreeRoam = true;
    if (MenuWidget) { MenuWidget->RemoveFromParent(); MenuWidget = nullptr; }
    HUDWidget = CreateWidget<UHorizonHUDWidget>(this, UHorizonHUDWidget::StaticClass());
    if (HUDWidget) HUDWidget->AddToViewport(5);
    SetShowMouseCursor(false);
    SetInputMode(FInputModeGameOnly());
}
void AHorizonPlayerController::ToggleVehicle()
{
    if (!bInFreeRoam || !GetWorld()) return;
    if (Cast<AHorizonVehicle>(GetPawn()))
    {
        if (StoredCharacter)
        {
            const FVector ExitLocation = GetPawn()->GetActorLocation() + GetPawn()->GetActorRightVector() * 280.f;
            StoredCharacter->SetActorLocation(ExitLocation);
            if (StoredCharacter->GetCharacterMovement())
                StoredCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
            Possess(StoredCharacter);
            StoredCharacter = nullptr;
        }
        return;
    }

    AHorizonCharacter* Character = Cast<AHorizonCharacter>(GetPawn());
    if (!Character) return;
    AHorizonVehicle* NearestVehicle = nullptr;
    float NearestDistance = 520.f;
    for (TActorIterator<AHorizonVehicle> It(GetWorld()); It; ++It)
    {
        const float Distance = FVector::Dist(Character->GetActorLocation(), It->GetActorLocation());
        if (Distance < NearestDistance) { NearestDistance = Distance; NearestVehicle = *It; }
    }
    if (NearestVehicle)
    {
        StoredCharacter = Character;
        if (StoredCharacter->GetCharacterMovement())
            StoredCharacter->GetCharacterMovement()->DisableMovement();
        Possess(NearestVehicle);
    }
}
