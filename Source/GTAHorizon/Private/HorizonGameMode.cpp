#include "HorizonGameMode.h"
#include "HorizonCharacter.h"
#include "HorizonPlayerController.h"
#include "HorizonCity.h"
#include "HorizonVehicle.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"

AHorizonGameMode::AHorizonGameMode()
{
    DefaultPawnClass = AHorizonCharacter::StaticClass();
    PlayerControllerClass = AHorizonPlayerController::StaticClass();
}
void AHorizonGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
    if (!GetWorld()) return;
    GetWorld()->SpawnActor<AHorizonCity>(FVector::ZeroVector, FRotator::ZeroRotator);
    GetWorld()->SpawnActor<AHorizonVehicle>(FVector(350.f, 0.f, 8.f), FRotator::ZeroRotator);
    FActorSpawnParameters Params;
    Params.Name = TEXT("HorizonPlayerStart");
    GetWorld()->SpawnActor<APlayerStart>(FVector(0.f, 0.f, 180.f), FRotator::ZeroRotator, Params);
}
