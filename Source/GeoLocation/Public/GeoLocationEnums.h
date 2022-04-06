/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"

/**
 * Enum for Geo Location Android Priority
 */
UENUM(BlueprintType)
enum class EGeoLocationAndroidPriority : uint8
{
	BalancedPowerAccuracy UMETA(DisplayName = "Balanced Power Accuracy"),
	HighAccuracy UMETA(DisplayName = "High Accuracy"),
	LowPower UMETA(DisplayName = "Low Power"),
	NoPower UMETA(DisplayName = "No Power")
};

/**
 * Enum for Geo Location Android Heading Delay
 */
UENUM(BlueprintType)
enum class EGeoLocationAndroidHeadingDelay : uint8
{
	SensorDelayGame UMETA(DisplayName = "Sensor Delay Game"),
	SensorDelayFastest UMETA(DisplayName = "Sensor Delay Fastest"),
	SensorDelayNormal UMETA(DisplayName = "Sensor Delay Normal"),
	SensorDelayUI UMETA(DisplayName = "Sensor Delay UI")
};

/**
 * Enum for Geo Location iOS Accuracy
 */
UENUM(BlueprintType)
enum class EGeoLocationIOSAccuracy : uint8
{
	BestForNavigation UMETA(DisplayName = "Best For Navigation"),
	Best UMETA(DisplayName = "Best"),
	NearestTenMeters UMETA(DisplayName = "Nearest Ten Meters"),
	HundredMeters UMETA(DisplayName = "Hundred Meters"),
	Kilometer UMETA(DisplayName = "Kilometer"),
	ThreeKilometers UMETA(DisplayName = "Three Kilometers")
};

/**
 * Enum for Geo Location Presets
 */
UENUM(BlueprintType)
enum class EGeoLocationPreset : uint8
{
	Glasgow UMETA(DisplayName = "Glasgow"),
	London UMETA(DisplayName = "London"),
	Berlin UMETA(DisplayName = "Berlin"),
	Moscow UMETA(DisplayName = "Moscow"),
	SanFrancisco UMETA(DisplayName = "San Francisco"),
	Shanghai UMETA(DisplayName = "Shanghai"),
	Toyko UMETA(DisplayName = "Toyko")
};

/**
 * Enum for Geo Fence Events
 */
UENUM()
enum class EGeoFenceEvent : uint8
{
	Begin,
	End,
	NoChange
};

/**
 * Enum for Geo Location Device Orientation
 */
UENUM()
enum class EGeoLocationDeviceOrientation : uint8
{
	Unknown UMETA(DisplayName = "Unknown"),
	Portrait UMETA(DisplayName = "Portrait"),
	PortraitUpsideDown UMETA(DisplayName = "Portrait Upside Down"),
	LandscapeLeft UMETA(DisplayName = "Landscape Left"),
	LandscapeRight UMETA(DisplayName = "Landscape Right")
};
