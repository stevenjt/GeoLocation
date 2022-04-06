/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#include "GeoLocationComponent.h"
#include "GeoLocation.h"
#include "GeoLocationProvider.h"

void UGeoLocationComponent::StartPositionUpdates()
{
	if (!Running && !SingleRequestRunning)
	{
		Running = true;
		LastPosition = NewObject<UGeoLocationPosition>();

		this->AddLocationDelegates();

		FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->StartPositionUpdate();
	}
}

void UGeoLocationComponent::StopPositionUpdates()
{
	if (Running && !SingleRequestRunning)
	{
		this->RemoveLocationDelegates();

		if (!FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->LocationUpdateDelegate.IsBound())
		{
			FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->StopPositionUpdate();
		}
		
		Running = false;
	}
}

void UGeoLocationComponent::RequestSinglePositionUpdate()
{
	if (!Running && !SingleRequestRunning)
	{
		SingleRequestRunning = true;
		LastPosition = NewObject<UGeoLocationPosition>();

		this->AddLocationDelegates();

		FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->RequestSinglePositionUpdate();
	}
}

bool UGeoLocationComponent::IsRunning()
{
	return Running;
}

UGeoLocationPosition* UGeoLocationComponent::GetLastPosition()
{
	return LastPosition;
}

void UGeoLocationComponent::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->StopPositionUpdate();

	FGeoLocationModule::Get().ShutdownPlatformProvider();
}

void UGeoLocationComponent::AddLocationDelegates()
{
	FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->LocationUpdateDelegate.AddUniqueDynamic(this, &UGeoLocationComponent::LocationUpdate);
	FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->LocationErrorDelegate.AddUniqueDynamic(this, &UGeoLocationComponent::LocationError);
}

void UGeoLocationComponent::RemoveLocationDelegates()
{
	if (FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->LocationUpdateDelegate.IsAlreadyBound(this, &UGeoLocationComponent::LocationUpdate))
	{
		FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->LocationUpdateDelegate.RemoveDynamic(this, &UGeoLocationComponent::LocationUpdate);
	}

	if (FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->LocationErrorDelegate.IsAlreadyBound(this, &UGeoLocationComponent::LocationError))
	{
		FGeoLocationModule::Get().GetPlatformProvider(GetWorld())->LocationErrorDelegate.RemoveDynamic(this, &UGeoLocationComponent::LocationError);
	}
}

void UGeoLocationComponent::LocationUpdate(double latitude, double longitude, double elevation, double horizontalAccuracy, double verticalAccuracy, double bearing, double speed, int64 time)
{
	LastPosition->SetLocation(latitude, longitude, elevation);
	LastPosition->SetAccuracy(horizontalAccuracy, verticalAccuracy);
	LastPosition->SetBearing(bearing);
	LastPosition->SetSpeed(speed);
	LastPosition->SetTime(time);

	LocationUpdateDelegate.Broadcast(LastPosition);

	if (this->RespondsToGeoFences)
	{
		// Check this new location with geo fences (if any exist)
		for (int i = 0; i < FGeoLocationModule::Get().GeoFences().Num(); i++)
		{
			UGeoFenceComponent* geoFenceComponent = FGeoLocationModule::Get().GeoFences()[i];
			switch (geoFenceComponent->GetGeoFenceEvent(this))
			{
			case EGeoFenceEvent::Begin:
				this->OnGeoFenceBeginOverlap.Broadcast(geoFenceComponent);
				break;
			case EGeoFenceEvent::End:
				this->OnGeoFenceEndOverlap.Broadcast(geoFenceComponent);
				break;
			case EGeoFenceEvent::NoChange:
				break;
			default:
				break;
			}
		}
	}

	if (SingleRequestRunning)
	{
		this->RemoveLocationDelegates();

		SingleRequestRunning = false;
	}
}

void UGeoLocationComponent::LocationError(FString message, int code)
{
	LocationErrorDelegate.Broadcast(message, code);

	if (SingleRequestRunning)
	{
		this->RemoveLocationDelegates();

		SingleRequestRunning = false;
	}
}
