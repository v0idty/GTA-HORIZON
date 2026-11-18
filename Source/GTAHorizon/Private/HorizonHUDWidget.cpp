#include "HorizonHUDWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HorizonCharacter.h"
#include "HorizonVehicle.h"
#include "HorizonPlayerController.h"

namespace
{
    UButton* MakeTouchButton(UWidgetTree* Tree, UCanvasPanel* Canvas, const TCHAR* Name,
        const FString& Label, FVector2D Anchor, FVector2D Size)
    {
        UButton* Button = Tree->ConstructWidget<UButton>(UButton::StaticClass(), FName(Name));
        Button->SetBackgroundColor(FLinearColor(.015f,.07f,.13f,.72f));
        UTextBlock* Text = Tree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
        Text->SetText(FText::FromString(Label));
        FSlateFontInfo Font; Font.Size = 25;
        Text->SetFont(Font);
        Text->SetColorAndOpacity(FSlateColor(FLinearColor::White));
        Text->SetJustification(ETextJustify::Center);
        Button->AddChild(Text);
        UCanvasPanelSlot* Slot = Canvas->AddChildToCanvas(Button);
        Slot->SetAnchors(FAnchors(Anchor.X, Anchor.Y));
        Slot->SetAlignment(FVector2D(.5f,.5f));
        Slot->SetSize(Size);
        return Button;
    }
}
void UHorizonHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (!WidgetTree) return;
    UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("HUDCanvas"));
    WidgetTree->RootWidget = Canvas;

    UTextBlock* Brand = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Brand"));
    Brand->SetText(FText::FromString(TEXT("HORIZON CITY  /  FREE ROAM")));
    FSlateFontInfo BrandFont; BrandFont.Size = 20;
    Brand->SetFont(BrandFont);
    Brand->SetColorAndOpacity(FSlateColor(FLinearColor(.65f,.87f,1.f)));
    UCanvasPanelSlot* BrandSlot = Canvas->AddChildToCanvas(Brand);
    BrandSlot->SetAnchors(FAnchors(.025f,.035f));
    BrandSlot->SetAutoSize(true);

    UButton* Forward = MakeTouchButton(WidgetTree,Canvas,TEXT("MoveForward"),TEXT("UP"),FVector2D(.13f,.77f),FVector2D(104,86));
    UButton* Back = MakeTouchButton(WidgetTree,Canvas,TEXT("MoveBack"),TEXT("DOWN"),FVector2D(.13f,.94f),FVector2D(104,86));
    UButton* Left = MakeTouchButton(WidgetTree,Canvas,TEXT("MoveLeft"),TEXT("LEFT"),FVector2D(.055f,.855f),FVector2D(104,86));
    UButton* Right = MakeTouchButton(WidgetTree,Canvas,TEXT("MoveRight"),TEXT("RIGHT"),FVector2D(.205f,.855f),FVector2D(104,86));
    Forward->OnPressed.AddDynamic(this,&UHorizonHUDWidget::ForwardPressed);
    Forward->OnReleased.AddDynamic(this,&UHorizonHUDWidget::ForwardReleased);
    Back->OnPressed.AddDynamic(this,&UHorizonHUDWidget::BackPressed);
    Back->OnReleased.AddDynamic(this,&UHorizonHUDWidget::BackReleased);
    Left->OnPressed.AddDynamic(this,&UHorizonHUDWidget::LeftPressed);
    Left->OnReleased.AddDynamic(this,&UHorizonHUDWidget::LeftReleased);
    Right->OnPressed.AddDynamic(this,&UHorizonHUDWidget::RightPressed);
    Right->OnReleased.AddDynamic(this,&UHorizonHUDWidget::RightReleased);

    UButton* Jump = MakeTouchButton(WidgetTree,Canvas,TEXT("Jump"),TEXT("JUMP"),FVector2D(.82f,.87f),FVector2D(150,88));
    Jump->OnClicked.AddDynamic(this,&UHorizonHUDWidget::JumpClicked);
    UButton* Vehicle = MakeTouchButton(WidgetTree,Canvas,TEXT("Vehicle"),TEXT("CAR"),FVector2D(.92f,.72f),FVector2D(150,88));
    Vehicle->OnClicked.AddDynamic(this,&UHorizonHUDWidget::VehicleClicked);
    UButton* Brake = MakeTouchButton(WidgetTree,Canvas,TEXT("Brake"),TEXT("BRAKE"),FVector2D(.82f,.68f),FVector2D(150,88));
    Brake->OnPressed.AddDynamic(this,&UHorizonHUDWidget::BrakePressed);
    Brake->OnReleased.AddDynamic(this,&UHorizonHUDWidget::BrakeReleased);
}
void UHorizonHUDWidget::RefreshTouchInput()
{
    const float Throttle=(bForward?1.f:0.f)-(bBack?1.f:0.f);
    const float Steering=(bRight?1.f:0.f)-(bLeft?1.f:0.f);
    if (AHorizonCharacter* Character = Cast<AHorizonCharacter>(GetOwningPlayerPawn()))
        Character->SetTouchMove(FVector2D(Steering,Throttle));
    else if (AHorizonVehicle* Vehicle = Cast<AHorizonVehicle>(GetOwningPlayerPawn()))
        Vehicle->SetTouchControls(Throttle,Steering,bBrake?1.f:0.f);
}
void UHorizonHUDWidget::ForwardPressed(){bForward=true;RefreshTouchInput();}
void UHorizonHUDWidget::ForwardReleased(){bForward=false;RefreshTouchInput();}
void UHorizonHUDWidget::BackPressed(){bBack=true;RefreshTouchInput();}
void UHorizonHUDWidget::BackReleased(){bBack=false;RefreshTouchInput();}
void UHorizonHUDWidget::LeftPressed(){bLeft=true;RefreshTouchInput();}
void UHorizonHUDWidget::LeftReleased(){bLeft=false;RefreshTouchInput();}
void UHorizonHUDWidget::RightPressed(){bRight=true;RefreshTouchInput();}
void UHorizonHUDWidget::RightReleased(){bRight=false;RefreshTouchInput();}
void UHorizonHUDWidget::BrakePressed(){bBrake=true;RefreshTouchInput();}
void UHorizonHUDWidget::BrakeReleased(){bBrake=false;RefreshTouchInput();}
void UHorizonHUDWidget::JumpClicked()
{
    if (AHorizonCharacter* Character = Cast<AHorizonCharacter>(GetOwningPlayerPawn())) Character->Jump();
}
void UHorizonHUDWidget::VehicleClicked()
{
    if (AHorizonPlayerController* PC = Cast<AHorizonPlayerController>(GetOwningPlayer())) PC->ToggleVehicle();
}
