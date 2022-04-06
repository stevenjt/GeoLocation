/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "Actor.h"
#include "GeoLocationEnums.h"
#include "GeoLocationPosition.h"
#include "GeoHeading.h"

#include "GeoLocationProvider.generated.h"

/**
 * Base class for the geo location providers
 */
UCLASS(Abstract)
class AGeoLocationProvider : public AActor
{

	GENERATED_BODY()

	/* Location Update Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_EightParams(FLocationUpdateDelegate, double, latitude, double, longitude, double, elevation, double, horizontalAccuracy, double, verticalAccuracy, double, bearing, double, speed, int64, time);

	/* Location Error Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLocationErrorDelegate, FString, message, int, code);

	/* Heading Update Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHeadingUpdateDelegate, FGeoHeading, heading);

	/* Heading Error Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHeadingErrorDelegate, FString, message);

public:

	/**
	 * Setup the geo provider. Derived platform providers can override this.
	 */
	UFUNCTION()
	virtual void Setup(UWorld* validWorld);

	/**
	 * Start the geo provider position updating. This should be implemented by derived platform providers.
	 */
	UFUNCTION()
	virtual void StartPositionUpdate() PURE_VIRTUAL(AGeoLocationProviderStartPositionUpdate,);

	/**
	 * Stop the geo provider position updating. This should be implemented by derived platform providers.
	 */
	UFUNCTION()
	virtual void StopPositionUpdate() PURE_VIRTUAL(AGeoLocationProviderStopPositionUpdate,);

	/**
	 * Request a single position update. This should be implemented by derived platform providers.
	 */
	UFUNCTION()
	virtual void RequestSinglePositionUpdate() PURE_VIRTUAL(AGeoLocationProviderGetCurrentPosition,);

	/**
	 * Location Error
	 */
	UFUNCTION()
	virtual void LocationError() PURE_VIRTUAL(AGeoLocationProviderLocationError, );

	/**
	 * Start the geo provider heading updating. This should be implemented by derived platform providers.
	 */
	UFUNCTION()
	virtual void StartHeadingUpdate() PURE_VIRTUAL(AGeoLocationProviderStartHeadingUpdate, );

	/**
	 * Stop the geo provider heading updating. This should be implemented by derived platform providers.
	 */
	UFUNCTION()
	virtual void StopHeadingUpdate() PURE_VIRTUAL(AGeoLocationProviderStopHeadingUpdate, );

	/**
	 * Request a single heading update. This should be implemented by derived platform providers.
	 */
	UFUNCTION()
	virtual void RequestSingleHeadingUpdate() PURE_VIRTUAL(AGeoLocationProviderRequestSingleHeadingUpdate, );

	/**
	 * Check Permissions
	 */
	UFUNCTION()
	virtual void CheckPermissions();

	/**
	 * Get Device Orientation
	 */
	UFUNCTION()
	virtual EGeoLocationDeviceOrientation GetDeviceOrientation() PURE_VIRTUAL(AGeoLocationProviderGetDeviceOrientation, return EGeoLocationDeviceOrientation::Unknown;);

	/**
	 * Get Magnetic Declination
	 */
	UFUNCTION()
	virtual float GetMagneticDeclination(float latitude, float longitude, float altitude, int64 milliseconds) PURE_VIRTUAL(AGeoLocationProviderGetMagneticDeclination, return 0.0f;);

	/**
	 * Is True North Heading Supported By Platform
	 */
	UFUNCTION()
	virtual bool IsTrueNorthHeadingSupportedByPlatform()  PURE_VIRTUAL(AGeoLocationProviderIsTrueNorthHeadingSupportedByPlatform, return false;);

	UFUNCTION()
	virtual void OnPermissionsGranted(const TArray<FString> &permissions, const TArray<bool>& granted) PURE_VIRTUAL(AGeoLocationProviderOnPermissionsGranted, );

	/**
	 * Location Update Delegate
	 */
	UPROPERTY()
	FLocationUpdateDelegate LocationUpdateDelegate;

	/**
	 * Location Error Delegate
	 */
	FLocationErrorDelegate LocationErrorDelegate;

	/**
	 * Heading Update Delegate
	 */
	FHeadingUpdateDelegate HeadingUpdateDelegate;

	/**
	 * Heading Error Delegate
	 */
	FHeadingErrorDelegate HeadingErrorDelegate;

	/* UWorld reference */
	UPROPERTY()
	UWorld* world;

};
