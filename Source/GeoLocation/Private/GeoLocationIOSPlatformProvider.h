/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationProvider.h"
#include "GeoLocationEnums.h"

#if PLATFORM_IOS
#include <CoreLocation/CoreLocation.h>
#endif

#include "Misc/CoreDelegates.h"
#include "Kismet/BlueprintPlatformLibrary.h"

#include "GeoLocationIOSPlatformProvider.generated.h"

/**
 * Geo location provider for iOS
 */
UCLASS()
class AGeoLocationIOSPlatformProvider : public AGeoLocationProvider
{

	GENERATED_BODY()

public:

	/**
	 * Setup the geo location provider for iOS
	 */
	void Setup(UWorld* validWorld) override;

	/**
	 * Start the geo location position updating for iOS
	 */
	void StartPositionUpdate() override;

	/**
	 * Stop the geo location position updating for iOS
	 */
	void StopPositionUpdate() override;

	/**
	 * Request a single position update for iOS
	 */
	void RequestSinglePositionUpdate();

	/**
	 * Start the heading updating for iOS
	 */
	void StartHeadingUpdate() override;

	/**
	 * Stop the heading updating for iOS
	 */
	void StopHeadingUpdate() override;

	/**
	 * Request a single heading update for iOS
	 */
	void RequestSingleHeadingUpdate();

	/**
	 * Get Device Orientation
	 */
	EGeoLocationDeviceOrientation GetDeviceOrientation();

	/**
	 * Get Is True North Heading Supported By Platform for iOS
	 */
	bool IsTrueNorthHeadingSupportedByPlatform();

	/**
	 * Orientation Changed Handler
	 */
	void OrientationChangedHandler(const int32 orientation);

private:

	/**
	 * Current Orientation
	 */
	EGeoLocationDeviceOrientation Orientation = EGeoLocationDeviceOrientation::Unknown;

#if PLATFORM_IOS
	/**
	 * Get the iOS accuracy setting from the iOS accuracy enum
	 */
	CLLocationAccuracy GetIOSAccuracy();

	/**
	 * Boolean for if a location update is running
	 */
	bool LocationUpdateRunning = false;

public:

	/**
	 * Last location from an update location request
	 */
	CLLocation* LastUpdateLocation = nil;
#endif
    
    /**
     * Boolean for if a heading update is running
     */
    bool HeadingUpdateRunning = false;
    
    /**
     * Boolean for if a single heading update is running
     */
    bool SingleHeadingUpdateRunning = false;

};

/* Static iOS Accuracy */
static EGeoLocationIOSAccuracy IOSAccuracy = EGeoLocationIOSAccuracy::Best;

/* Static iOS Minimum Distance */
static double IOSMinimumDistance = 0.0f;
