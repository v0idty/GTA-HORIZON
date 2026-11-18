#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HorizonMenuWidget.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHorizonStartRequested);

UCLASS()
class GTAHORIZON_API UHorizonMenuWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Horizon")
    FHorizonStartRequested OnStartRequested;
protected:
    virtual void NativeConstruct() override;
private:
    UFUNCTION() void HandleStartClicked();
};
