/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationProvider.h"
#include "GeoLocationEnums.h"

#include "GeoLocationHTML5PlatformProvider.generated.h"

/**
* Geo location provider for HTML5
*/
UCLASS()
class AGeoLocationHTML5PlatformProvider : public AGeoLocationProvider
{

	GENERATED_BODY()
	
public:

	/**
	* Setup the geo location provider for HTML5
	*/
	void Setup(UWorld* validWorld) override;

	/**
	* Start the geo location position updating for HTML5
	*/
	void StartPositionUpdate() override;

	/**
	* Stop the geo location position updating for HTML5
	*/
	void StopPositionUpdate() override;

	/**
	 * Request a single position update for HTML5
	 */
	void RequestSinglePositionUpdate();

	/**
	 * Start the heading updating for HTML5
	 */
	void StartHeadingUpdate() override;

	/**
	 * Stop the heading updating for HTML5
	 */
	void StopHeadingUpdate() override;

	/**
	 * Request a single heading update for HTML5
	 */
	void RequestSingleHeadingUpdate();

	/**
	 * Get Device Orientation
	 */
	EGeoLocationDeviceOrientation GetDeviceOrientation();

	/**
	 * Get Is True North Heading Supported By Platform for HTML5
	 */
	bool IsTrueNorthHeadingSupportedByPlatform();

private:

	/**
	 * Current Orientation
	 */
	EGeoLocationDeviceOrientation Orientation = EGeoLocationDeviceOrientation::Unknown;

};

/* Static HTML5 High Accuracy boolean */
static bool HTML5HighAccuracy = true;
