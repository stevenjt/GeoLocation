/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocation.h"
#include "GeoLocationProvider.h"
#include "GeoLocationPosition.h"

#include "GeoLocationEditorPlatformProvider.generated.h"

/* Glasgow latitude/longitude preset */
static const double GLASGOW_LATITUDE = 55.860548f;
static const double GLASGOW_LONGITUDE = -4.257032f;

/* London latitude/longitude preset */
static const double LONDON_LATITUDE = 51.507560f;
static const double LONDON_LONGITUDE = -0.128224f;

/* Berlin latitude/longitude preset */
static const double BERLIN_LATITUDE = 52.520036f;
static const double BERLIN_LONGITUDE = 13.405151f;

/* Moscow latitude/longitude preset */
static const double MOSCOW_LATITUDE = 55.754264f;
static const double MOSCOW_LONGITUDE = 37.620103f;

/* San Francisco latitude/longitude preset */
static const double SANFRANCISCO_LATITUDE = 37.779480f;
static const double SANFRANCISCO_LONGITUDE = -122.417764f;

/* Shanghai latitude/longitude preset */
static const double SHANGHAI_LATITUDE = 31.230774f;
static const double SHANGHAI_LONGITUDE = 121.473458f;

/* Toyko latitude/longitude preset */
static const double TOYKO_LATITUDE = 35.659641f;
static const double TOYKO_LONGITUDE = 139.700417f;

/**
 * Geo location provider for the Unreal Editor
 */
UCLASS()
class AGeoLocationEditorPlatformProvider : public AGeoLocationProvider
{

	GENERATED_BODY()

public:

	/**
	 * Setup the geo location provider for the Unreal Editor
	 */
	void Setup(UWorld* validWorld) override;

	/**
	 * Start the geo location position updating for the Unreal Editor
	 */
	void StartPositionUpdate() override;

	/**
	 * Stop the geo location position updating for the Unreal Editor
	 */
	void StopPositionUpdate() override;

	/**
	 * Request a single position update for the Unreal Editor
	 */
	void RequestSinglePositionUpdate();

	/**
	 * Start the heading updating for the Unreal Editor
	 */
	void StartHeadingUpdate() override;

	/**
	 * Stop the heading updating for the Unreal Editor
	 */
	void StopHeadingUpdate() override;

	/**
	 * Request a single heading update for the Unreal Editor
	 */
	void RequestSingleHeadingUpdate();

	/**
	 * Get Device Orientation
	 */
	EGeoLocationDeviceOrientation GetDeviceOrientation();

	/**
	 * Get Magnetic Declination for the Unreal Editor
	 */
	float GetMagneticDeclination(float latitude, float longitude, float altitude, int64 milliseconds);

	/**
	 * Get Is True North Heading Supported By Platform for the Unreal Editor
	 */
	bool IsTrueNorthHeadingSupportedByPlatform();

	/**
	 * Send location updates.
	 */
	UFUNCTION()
	void LocationUpdate();

	/**
	 * Send heading updates.
	 */
	UFUNCTION()
	void HeadingUpdate();

private:

	/* Location update timer handle */
	UPROPERTY()
	FTimerHandle locationTimerHandle;

	/* Heading update timer handle */
	UPROPERTY()
	FTimerHandle headingTimerHandle;

};

/* Static simulated latitude and longitude for the Editor Provider */
static double EditorSimulatedPositionLatitude = 0.0f;
static double EditorSimulatedPositionLongitude = 0.0f;

/* Static simulated elevation for the Editor Provider */
static double EditorSimulatedPositionElevation = 0.0f;

/* Static simulated magnetic north for the Editor Provider */
static double EditorSimulatedMagneticNorth = 0.0f;

/* Static simulated true north for the Editor Provider */
static double EditorSimulatedTrueNorth = 0.0f;

/* Static simulated heading calibrated for the Editor Provider */
static bool EditorSimulatedHeadingCalibrated = true;

/* Static simulated location interval time for the Editor Provider */
static float EditorLocationIntervalTime = 1.0f;

/* Static simulated heading interval time for the Editor Provider */
static float EditorHeadingIntervalTime = 1.0f;
