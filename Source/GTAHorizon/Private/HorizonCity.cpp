#include "HorizonCity.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"

AHorizonCity::AHorizonCity()
{
    PrimaryActorTick.bCanEverTick = false;
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) CubeMesh = Cube.Object;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (Sphere.Succeeded()) SphereMesh = Sphere.Object;
}
void AHorizonCity::BeginPlay()
{
    Super::BeginPlay();
    BuildCityBlockout();
    BuildLighting();
}
void AHorizonCity::AddBlock(FName Name, FVector Location, FVector Scale, FLinearColor Color)
{
    UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(this, Name);
    if (!Mesh || !CubeMesh) return;
    Mesh->SetupAttachment(SceneRoot);
    Mesh->SetStaticMesh(CubeMesh);
    Mesh->SetRelativeLocation(Location);
    Mesh->SetRelativeScale3D(Scale);
    Mesh->SetCollisionProfileName(TEXT("BlockAll"));
    Mesh->RegisterComponent();
    if (UMaterialInstanceDynamic* MID = Mesh->CreateAndSetMaterialInstanceDynamic(0))
    {
        MID->SetVectorParameterValue(TEXT("BaseColor"), Color);
        MID->SetVectorParameterValue(TEXT("Color"), Color);
    }
}
void AHorizonCity::BuildCityBlockout()
{
    AddBlock(TEXT("City Ground"), FVector(0, 0, -120), FVector(250, 280, 1), FLinearColor(0.12f,0.15f,0.18f));
    AddBlock(TEXT("Main Boulevard"), FVector(0, 0, -40), FVector(9, 140, .12f), FLinearColor(.035f,.04f,.055f));
    AddBlock(TEXT("Beachfront"), FVector(-10500, 8500, -65), FVector(55, 38, .2f), FLinearColor(.67f,.53f,.34f));
    AddBlock(TEXT("Ocean"), FVector(-16000, 13000, -180), FVector(90, 80, .2f), FLinearColor(.015f,.15f,.24f));
    FRandomStream Random(580);
    for (int32 Z = -6; Z <= 6; ++Z)
    {
        for (int32 X = -5; X <= 5; ++X)
        {
            if (FMath::Abs(X) <= 1) continue;
            const float Height = Random.FRandRange(900.f, 4200.f);
            const FVector Location(X * 1900.f, Z * 1900.f, Height * .5f - 30.f);
            const FVector Scale(Random.FRandRange(5.f, 9.f), Random.FRandRange(5.f, 9.f), Height / 100.f);
            const FLinearColor Facade(Random.FRandRange(.08f,.22f), Random.FRandRange(.12f,.25f), Random.FRandRange(.18f,.34f), 1.f);
            AddBlock(FName(*FString::Printf(TEXT("Tower_%d_%d"), X, Z)), Location, Scale, Facade);
        }
    }
    for (int32 Index = -65; Index <= 65; Index += 5)
    {
        AddBlock(FName(*FString::Printf(TEXT("LaneMark_%d"), Index)),
            FVector(0, Index * 200.f, -26.f), FVector(.10f, 1.4f, .025f), FLinearColor(.95f,.75f,.38f));
    }
    for (int32 Index = 0; Index < 26; ++Index)
    {
        const float Y = -12500.f + Index * 950.f;
        AddBlock(FName(*FString::Printf(TEXT("PalmTrunk_%d"), Index)),
            FVector(-9000.f, Y, 310.f), FVector(.22f,.22f,3.1f), FLinearColor(.28f,.13f,.055f));
        if (SphereMesh)
        {
            UStaticMeshComponent* Crown = NewObject<UStaticMeshComponent>(this);
            Crown->SetupAttachment(SceneRoot);
            Crown->SetStaticMesh(SphereMesh);
            Crown->SetRelativeLocation(FVector(-9000.f, Y, 680.f));
            Crown->SetRelativeScale3D(FVector(1.7f,1.7f,.55f));
            Crown->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            Crown->RegisterComponent();
        }
    }
}
void AHorizonCity::BuildLighting()
{
    if (ADirectionalLight* Sun = GetWorld()->SpawnActor<ADirectionalLight>())
    {
        Sun->SetActorRotation(FRotator(-28.f, -35.f, 0.f));
        Sun->GetLightComponent()->SetIntensity(5.f);
        Sun->GetLightComponent()->SetLightColor(FLinearColor(1.f,.72f,.52f));
    }
    if (ASkyLight* Sky = GetWorld()->SpawnActor<ASkyLight>())
        Sky->GetLightComponent()->SetIntensity(1.0f);
    if (AExponentialHeightFog* Fog = GetWorld()->SpawnActor<AExponentialHeightFog>())
    {
        Fog->GetComponent()->SetFogDensity(.008f);
        Fog->GetComponent()->SetFogInscatteringColor(FLinearColor(.28f,.33f,.48f));
    }
}
