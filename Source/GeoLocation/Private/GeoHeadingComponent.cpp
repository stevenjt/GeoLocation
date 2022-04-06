/**
 * GeoLocation
 *
 * Copyright (c) 2018 Steven Thompson
**/

#include "GeoHeadingComponent.h"
#include "GeoLocation.h"

UGeoHeadingComponent::UGeoHeadingComponent(const FObjectInitializer& ObjectInitializer)
{
	GeoLocationComponent = CreateDefaultSubobject<UGeoLocationComponent>(TEXT("GeoLocationComponent"));
	GeoLocationComponent->LocationUpdateDelegate.AddDynamic(this, &UGeoHeadingComponent::LocationUpdate);
}

void UGeoHeadingComponent::StartHeadingUpdates(bool calculateTrueNorth, bool adjustForScreenOrientation)
{
	if (!Running && !SingleRequestRunning)
	{
		CalculateTrueNorth = calculateTrueNorth;
		AdjustForScreenOrientation = adjustForScreenOrientation;

		if (CalculateTrueNorth)
		{
			this->GeoLocationComponent->StartPositionUpdates();
		}
		else
		{
			this->GeoLocationComponent->StopPositionUpdates();
		}

		Running = true;

		LastHeading.MagneticNorth = 0.0f;
		LastHeading.TrueNorth = 0.0f;
		LastHeading.Calibrated = false;

		this->AddHeadingDelegates();

		FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->StartHeadingUpdate();
	}
}

void UGeoHeadingComponent::StopHeadingUpdates()
{
	if (Running && !SingleRequestRunning)
	{
		this->RemoveHeadingDelegates();

		if (!FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->HeadingUpdateDelegate.IsBound())
		{
			FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->StopHeadingUpdate();
		}

		Running = false;
	}
}

void UGeoHeadingComponent::RequestSingleHeadingUpdate()
{
	if (!Running && !SingleRequestRunning)
	{
		SingleRequestRunning = true;
		LastHeading.MagneticNorth = 0.0f;
		LastHeading.TrueNorth = 0.0f;
		LastHeading.Calibrated = false;

		this->AddHeadingDelegates();

		FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->RequestSingleHeadingUpdate();
	}
}

bool UGeoHeadingComponent::IsRunning()
{
	return Running;
}

FGeoHeading UGeoHeadingComponent::GetLastHeading()
{
	return LastHeading;
}

bool UGeoHeadingComponent::IsTrueNorthHeadingSupportedByPlatform()
{
	return FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->IsTrueNorthHeadingSupportedByPlatform();
}

void UGeoHeadingComponent::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->StopHeadingUpdate();

	FGeoLocationModule::Get().ShutdownPlatformProvider();
}

void UGeoHeadingComponent::LocationUpdate(UGeoLocationPosition* position)
{
	CurrentLocation = position;
}

void UGeoHeadingComponent::AddHeadingDelegates()
{
	FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->HeadingUpdateDelegate.AddUniqueDynamic(this, &UGeoHeadingComponent::HeadingUpdate);
	FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->HeadingErrorDelegate.AddUniqueDynamic(this, &UGeoHeadingComponent::HeadingError);
}

void UGeoHeadingComponent::RemoveHeadingDelegates()
{
	if (FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->HeadingUpdateDelegate.IsAlreadyBound(this, &UGeoHeadingComponent::HeadingUpdate))
	{
		FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->HeadingUpdateDelegate.RemoveDynamic(this, &UGeoHeadingComponent::HeadingUpdate);
	}

	if (FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->HeadingErrorDelegate.IsAlreadyBound(this, &UGeoHeadingComponent::HeadingError))
	{
		FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->HeadingErrorDelegate.RemoveDynamic(this, &UGeoHeadingComponent::HeadingError);
	}
}

void UGeoHeadingComponent::HeadingUpdate(FGeoHeading heading)
{
#if PLATFORM_ANDROID
	if (CalculateTrueNorth && CurrentLocation != nullptr)
	{
		heading.TrueNorth = heading.MagneticNorth - FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->GetMagneticDeclination(CurrentLocation->GetLatitude(), CurrentLocation->GetLongitude(), CurrentLocation->GetElevation(), CurrentLocation->GetTime());
	}
#endif

	if (AdjustForScreenOrientation)
	{
		EGeoLocationDeviceOrientation orientation = FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->GetDeviceOrientation();
		switch (orientation)
		{
			case EGeoLocationDeviceOrientation::Portrait:
			case EGeoLocationDeviceOrientation::PortraitUpsideDown:
			{
				orientationModifier = 0.0f;
				break;
			}
			case EGeoLocationDeviceOrientation::LandscapeLeft:
			{
#if PLATFORM_ANDROID
				orientationModifier = 90.0f;
#elif PLATFORM_IOS
				orientationModifier = -90.0f;
#endif
				break;
			}
			case EGeoLocationDeviceOrientation::LandscapeRight:
			{
#if PLATFORM_ANDROID
				orientationModifier = -90.0f;
#elif PLATFORM_IOS
				orientationModifier = 90.0f;
#endif
				break;
			}
		}

		heading.MagneticNorth += orientationModifier;
		heading.TrueNorth += orientationModifier;
	}

	heading.MagneticNorth = fmod(heading.MagneticNorth + 360, 360);
	heading.TrueNorth = fmod(heading.TrueNorth + 360, 360);

	LastHeading = heading;

	HeadingUpdateDelegate.Broadcast(LastHeading);

	if (SingleRequestRunning)
	{
		this->RemoveHeadingDelegates();

		SingleRequestRunning = false;
	}
}

void UGeoHeadingComponent::HeadingError(FString message)
{
	HeadingErrorDelegate.Broadcast(message);
}
