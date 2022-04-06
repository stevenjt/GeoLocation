/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#include "GeoLocationSettings.h"
#include "GeoLocation.h"
#include "GeoLocationProvider.h"
#include "GeoLocationEditorPlatformProvider.h"
#include "GeoLocationIOSPlatformProvider.h"
#include "GeoLocationHTML5PlatformProvider.h"
#include "GeoLocationIOSPlatformProvider.h"

void UGeoLocationSettings::GeoLocationSetAndroidIntervalTime(int intervalTime)
{
	AndroidIntervalTime = intervalTime;
}

void UGeoLocationSettings::GeoLocationSetAndroidFastestIntervalTime(int fastestIntervalTime)
{
	AndroidFastestIntervalTime = fastestIntervalTime;
}

void UGeoLocationSettings::GeoLocationSetAndroidPriority(EGeoLocationAndroidPriority priority)
{
	AndroidPriority = priority;
}

void UGeoLocationSettings::GeoLocationSetAndroidHeadingDelay(EGeoLocationAndroidHeadingDelay headingDelay)
{
	AndroidHeadingDelay = headingDelay;
}

void UGeoLocationSettings::GeoLocationSetAndroidMinimumDistance(float minimumDistance)
{
	AndroidMinimumDistance = minimumDistance;
}

void UGeoLocationSettings::GeoLocationSetHTML5HighAccuracy(bool highAccuracy)
{
	HTML5HighAccuracy = highAccuracy;
}

void UGeoLocationSettings::GeoLocationSetIOSAccuracy(EGeoLocationIOSAccuracy accuracy)
{
	IOSAccuracy = accuracy;
}

void UGeoLocationSettings::GeoLocationSetIOSMinimumDistance(float minimumDistance)
{
	IOSMinimumDistance = minimumDistance;
}

void UGeoLocationSettings::GeoLocationSetEditorSimulatedGeoLocationPreset(EGeoLocationPreset preset)
{
#if WITH_EDITOR
	if (preset == EGeoLocationPreset::Glasgow)
	{
		EditorSimulatedPositionLatitude = GLASGOW_LATITUDE;
		EditorSimulatedPositionLongitude = GLASGOW_LONGITUDE;
	}
	else if (preset == EGeoLocationPreset::London)
	{
		EditorSimulatedPositionLatitude = LONDON_LATITUDE;
		EditorSimulatedPositionLongitude = LONDON_LONGITUDE;
	}
	else if (preset == EGeoLocationPreset::Berlin)
	{
		EditorSimulatedPositionLatitude = BERLIN_LATITUDE;
		EditorSimulatedPositionLongitude = BERLIN_LONGITUDE;
	}
	else if (preset == EGeoLocationPreset::Moscow)
	{
		EditorSimulatedPositionLatitude = MOSCOW_LATITUDE;
		EditorSimulatedPositionLongitude = MOSCOW_LONGITUDE;
	}
	else if (preset == EGeoLocationPreset::SanFrancisco)
	{
		EditorSimulatedPositionLatitude = SANFRANCISCO_LATITUDE;
		EditorSimulatedPositionLongitude = SANFRANCISCO_LONGITUDE;
	}
	else if (preset == EGeoLocationPreset::Shanghai)
	{
		EditorSimulatedPositionLatitude = SHANGHAI_LATITUDE;
		EditorSimulatedPositionLongitude = SHANGHAI_LONGITUDE;
	}
	else if (preset == EGeoLocationPreset::Toyko)
	{
		EditorSimulatedPositionLatitude = TOYKO_LATITUDE;
		EditorSimulatedPositionLongitude = TOYKO_LONGITUDE;
	}
#endif
}

void UGeoLocationSettings::GeoLocationSetEditorSimulatedGeoLocationCustom(float latitude, float longitude)
{
#if WITH_EDITOR
	EditorSimulatedPositionLatitude = latitude;
	EditorSimulatedPositionLongitude = longitude;
#endif
}

void UGeoLocationSettings::GeoLocationSetEditorSimulatedHeadingMagneticNorthCustom(float magneticNorth)
{
#if WITH_EDITOR
	EditorSimulatedMagneticNorth = magneticNorth;
#endif
}

void UGeoLocationSettings::GeoLocationSetEditorSimulatedHeadingTrueNorthCustom(float trueNorth)
{
#if WITH_EDITOR
	EditorSimulatedTrueNorth = trueNorth;
#endif
}

void UGeoLocationSettings::GeoLocationSetEditorSimulatedIntervalTime(float intervalTime)
{
#if WITH_EDITOR
	EditorLocationIntervalTime = intervalTime;
#endif
}

void UGeoLocationSettings::GeoLocationSetEditorSimulatedHeadingIntervalTime(float intervalTime)
{
#if WITH_EDITOR
	EditorHeadingIntervalTime = intervalTime;
#endif
}
