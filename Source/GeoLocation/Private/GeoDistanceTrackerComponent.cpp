/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#include "GeoDistanceTrackerComponent.h"

UGeoDistanceTrackerComponent::UGeoDistanceTrackerComponent(const FObjectInitializer& ObjectInitializer)
{
	GeoLocationComponent = CreateDefaultSubobject<UGeoLocationComponent>(TEXT("GeoLocationComponent"));
	GeoLocationComponent->LocationUpdateDelegate.AddDynamic(this, &UGeoDistanceTrackerComponent::LocationUpdate);

	LastGeoLocationPosition = CreateDefaultSubobject<UGeoLocationPosition>(TEXT("LastGeoLocationPosition"));
}

void UGeoDistanceTrackerComponent::StartDistanceTracking()
{
	if (!Running)
	{
		Running = true;
		GeoLocationComponent->StartPositionUpdates();
	}
}

void UGeoDistanceTrackerComponent::StopDistanceTracking()
{
	if (Running)
	{
		Running = false;
		GeoLocationComponent->StopPositionUpdates();
		LastGeoLocationPositionReady = false;
	}
}

float UGeoDistanceTrackerComponent::GetDistanceTravelled()
{
	return DistanceTravelled;
}

float UGeoDistanceTrackerComponent::GetCurrentSpeed()
{
	return CurrentSpeed;
}

void UGeoDistanceTrackerComponent::ResetDistanceTracking()
{
	DistanceTravelled = 0;
}

bool UGeoDistanceTrackerComponent::IsRunning()
{
	return Running;
}

void UGeoDistanceTrackerComponent::LocationUpdate_TestingOnly(FGeoCoordinate position, FDateTime time)
{
	UGeoLocationPosition* locationPosition = NewObject<UGeoLocationPosition>();
	locationPosition->SetLocation(position);

	if (time != NULL)
	{
		locationPosition->SetUpdatedTime(time);
	}

	IgnoreSpeedChecks = true;
	this->LocationUpdate(locationPosition);
}

void UGeoDistanceTrackerComponent::LocationUpdate(UGeoLocationPosition* position)
{
	if (LastGeoLocationPositionReady)
	{
		float distanceKilometres = LastGeoLocationPosition->CalculateDistanceTo(position);

		// Calculate the current speed
		double microsecondsSinceLastPosition = (position->GetLastUpdated() - LastGeoLocationPosition->GetLastUpdated()).GetTotalMicroseconds();
		CurrentSpeed = (3600.0f / (microsecondsSinceLastPosition * 0.000001)) * distanceKilometres;

		bool validSpeed = CurrentSpeed <= MaximumValidSpeed && CurrentSpeed >= MinimumValidSpeed;

		if ((validSpeed || !UseSpeedLimits) || IgnoreSpeedChecks)
		{
			// Add to distance travelled
			DistanceTravelled += distanceKilometres * 1000;
			DistanceTravelledUpdate.Broadcast(DistanceTravelled);

			IgnoreSpeedChecks = false;
		}
		else
		{
			if (CurrentSpeed >= MaximumValidSpeed)
			{
				ErrorUpdate.Broadcast("Travelling too fast");
			}
			else if (CurrentSpeed <= MinimumValidSpeed)
			{
				ErrorUpdate.Broadcast("Travelling too slow");
			}
		}

		SpeedUpdate.Broadcast(CurrentSpeed);
	}

	LastGeoLocationPosition->SetLocation(position->GetLatitude(), position->GetLongitude(), position->GetElevation());
	LastGeoLocationPositionReady = true;
}
