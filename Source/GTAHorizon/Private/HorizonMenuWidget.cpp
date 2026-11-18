#include "HorizonMenuWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UHorizonMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (!WidgetTree) return;
    UCanvasPanel* Canvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("MenuCanvas"));
    WidgetTree->RootWidget = Canvas;

    UImage* Backdrop = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), TEXT("Backdrop"));
    Backdrop->SetColorAndOpacity(FLinearColor(.012f,.025f,.07f,1.f));
    UCanvasPanelSlot* BackdropSlot = Canvas->AddChildToCanvas(Backdrop);
    BackdropSlot->SetAnchors(FAnchors(0.f,0.f,1.f,1.f));
    BackdropSlot->SetOffsets(FMargin(0.f));

    UTextBlock* Eyebrow = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Eyebrow"));
    Eyebrow->SetText(FText::FromString(TEXT("A NEW ERA OF OPEN WORLD")));
    FSlateFontInfo SmallFont; SmallFont.Size = 22;
    Eyebrow->SetFont(SmallFont);
    Eyebrow->SetColorAndOpacity(FSlateColor(FLinearColor(.58f,.82f,1.f)));
    UCanvasPanelSlot* EyebrowSlot = Canvas->AddChildToCanvas(Eyebrow);
    EyebrowSlot->SetAnchors(FAnchors(.12f,.28f,.82f,.38f));
    EyebrowSlot->SetAlignment(FVector2D(.5f,.5f));
    EyebrowSlot->SetAutoSize(true);

    UTextBlock* Title = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Title"));
    Title->SetText(FText::FromString(TEXT("GTA HORIZON")));
    FSlateFontInfo TitleFont; TitleFont.Size = 92;
    Title->SetFont(TitleFont);
    Title->SetColorAndOpacity(FSlateColor(FLinearColor(.12f,.72f,1.f)));
    UCanvasPanelSlot* TitleSlot = Canvas->AddChildToCanvas(Title);
    TitleSlot->SetAnchors(FAnchors(.08f,.34f,.92f,.58f));
    TitleSlot->SetAlignment(FVector2D(.5f,.5f));
    TitleSlot->SetAutoSize(true);

    UTextBlock* Tagline = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Tagline"));
    Tagline->SetText(FText::FromString(TEXT("A CITY WITHOUT LIMITS  -  VERSION 0.1")));
    FSlateFontInfo TagFont; TagFont.Size = 24;
    Tagline->SetFont(TagFont);
    Tagline->SetColorAndOpacity(FSlateColor(FLinearColor(.88f,.92f,1.f)));
    UCanvasPanelSlot* TagSlot = Canvas->AddChildToCanvas(Tagline);
    TagSlot->SetAnchors(FAnchors(.15f,.56f,.85f,.65f));
    TagSlot->SetAlignment(FVector2D(.5f,.5f));
    TagSlot->SetAutoSize(true);

    UButton* StartButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("StartButton"));
    StartButton->SetBackgroundColor(FLinearColor(.02f,.35f,.62f,.96f));
    StartButton->OnClicked.AddDynamic(this, &UHorizonMenuWidget::HandleStartClicked);
    UTextBlock* StartLabel = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("StartLabel"));
    StartLabel->SetText(FText::FromString(TEXT("START FREE ROAM")));
    FSlateFontInfo ButtonFont; ButtonFont.Size = 28; ButtonFont.TypefaceFontName = TEXT("Bold");
    StartLabel->SetFont(ButtonFont);
    StartLabel->SetColorAndOpacity(FSlateColor(FLinearColor::White));
    StartLabel->SetJustification(ETextJustify::Center);
    StartButton->AddChild(StartLabel);
    UCanvasPanelSlot* ButtonSlot = Canvas->AddChildToCanvas(StartButton);
    ButtonSlot->SetAnchors(FAnchors(.5f,.72f));
    ButtonSlot->SetAlignment(FVector2D(.5f,.5f));
    ButtonSlot->SetSize(FVector2D(440.f,96.f));

    UTextBlock* Footer = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Footer"));
    Footer->SetText(FText::FromString(TEXT("ORIGINAL MOBILE OPEN-WORLD PROJECT")));
    FSlateFontInfo FooterFont; FooterFont.Size = 16;
    Footer->SetFont(FooterFont);
    Footer->SetColorAndOpacity(FSlateColor(FLinearColor(.43f,.54f,.66f)));
    UCanvasPanelSlot* FooterSlot = Canvas->AddChildToCanvas(Footer);
    FooterSlot->SetAnchors(FAnchors(.06f,.91f));
    FooterSlot->SetAutoSize(true);
}
void UHorizonMenuWidget::HandleStartClicked() { OnStartRequested.Broadcast(); }
