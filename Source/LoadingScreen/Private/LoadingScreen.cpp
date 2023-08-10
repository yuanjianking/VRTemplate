// Copyright Epic Games, Inc. All Rights Reserved.

#include "LoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!
struct LoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	LoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject* CachedResourceObject = GetResourceObject())
		{
			Collector.AddReferencedObject(CachedResourceObject);
		}
	}
};

class LoadingScreenWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(LoadingScreenWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		// Load version of the logo with text baked in, path is hardcoded because this loads very early in startup
		static const FName LoadingScreenName(TEXT("/Game/UI/loading.loading"));
		

		LoadingScreenBrushPtr = MakeShareable(new LoadingScreenBrush(LoadingScreenName, FVector2D(1920, 1080)));
		
		FSlateBrush *BGBrush = new FSlateBrush();
		BGBrush->TintColor = FLinearColor(0.034f, 0.034f, 0.034f, 1.0f);

		ChildSlot
			[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)	
				.BorderImage(BGBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(LoadingScreenBrushPtr.Get())
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(10.0f))
				[
					SNew(SThrobber)
					.Visibility(this, &LoadingScreenWidget::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	/** Rather to show the ... indicator */
	EVisibility GetLoadIndicatorVisibility() const
	{
		bool Vis =  GetMoviePlayer()->IsLoadingFinished();
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}
	
	/** Loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrushPtr;
};

class FLoadingScreenModule : public ILoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		// Force load for cooker reference
		LoadObject<UObject>(nullptr, TEXT("/Game/UI/loading.loading") );

		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}
	
	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	{
		FLoadingScreenAttributes LoadingScreenAttributes;
		LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = !bPlayUntilStopped;
		LoadingScreenAttributes.bWaitForManualStop = bPlayUntilStopped;
		LoadingScreenAttributes.bAllowEngineTick = bPlayUntilStopped;
		LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = PlayTime;
		LoadingScreenAttributes.WidgetLoadingScreen = SNew(LoadingScreenWidget);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
		UE_LOG(LogTemp, Warning, TEXT("SetupLoadingScreen"));
	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreenAttributes;
		LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 5.f;
		LoadingScreenAttributes.WidgetLoadingScreen = SNew(LoadingScreenWidget);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
	}

};

IMPLEMENT_GAME_MODULE(FLoadingScreenModule, LoadingScreen);
