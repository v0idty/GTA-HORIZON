#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HorizonCity.generated.h"
class UStaticMesh;
class USceneComponent;

UCLASS()
class GTAHORIZON_API AHorizonCity : public AActor
{
    GENERATED_BODY()
public:
    AHorizonCity();
    virtual void BeginPlay() override;
private:
    UPROPERTY() TObjectPtr<USceneComponent> SceneRoot;
    UPROPERTY() TObjectPtr<UStaticMesh> CubeMesh;
    UPROPERTY() TObjectPtr<UStaticMesh> SphereMesh;
    void BuildCityBlockout();
    void AddBlock(FName Name, FVector Location, FVector Scale, FLinearColor Color);
    void BuildLighting();
};
