#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HorizonGameMode.generated.h"
UCLASS()
class GTAHORIZON_API AHorizonGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    AHorizonGameMode();
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
