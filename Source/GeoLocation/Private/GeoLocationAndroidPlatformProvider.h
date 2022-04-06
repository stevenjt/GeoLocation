/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocation.h"
#include "GeoLocationProvider.h"
#include "GeoLocationEnums.h"
#include "GeoAndroidPermissionHandler.h"
#include "Async/Async.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "AndroidPermissionFunctionLibrary.h"
#include "AndroidPermissionCallbackProxy.h"
#endif

#include "GeoLocationAndroidPlatformProvider.generated.h"

/**
 * Geo location provider for Android
 */
UCLASS()
class AGeoLocationAndroidPlatformProvider : public AGeoLocationProvider
{

	GENERATED_BODY()

public:

	/**
	 * Setup the geo location provider for Android
	 */
	void Setup(UWorld* validWorld) override;

	/**
	 * Start the geo location position updating for Android
	 */
	void StartPositionUpdate() override;

	/**
	 * Stop the geo location position updating for Android
	 */
	void StopPositionUpdate() override;

	/**
	 * Request a single position update for Android
	 */
	void RequestSinglePositionUpdate();

	/**
	 * Start the heading updating for Android
	 */
	void StartHeadingUpdate() override;

	/**
	 * Stop the heading updating for Android
	 */
	void StopHeadingUpdate() override;

	/**
	 * Request a single heading update for Android
	 */
	void RequestSingleHeadingUpdate();

	/**
	 * Get Device Orientation
	 */
	EGeoLocationDeviceOrientation GetDeviceOrientation();

	/**
	 * Get Magnetic Declination for Android
	 */
	float GetMagneticDeclination(float latitude, float longitude, float altitude, int64 milliseconds);

	/**
	 * Get Is True North Heading Supported By Platform for Android
	 */
	bool IsTrueNorthHeadingSupportedByPlatform();

	/**
	 * OnPermissionsGranted
	 */
	void OnPermissionsGranted(const TArray<FString> &permissions, const TArray<bool>& granted) override;

	/**
	 * Check Permissions
	 */
	void CheckPermissions() override;

private:

	/**
	 * Get the Android priority value from the Android Priority enum
	 */
	UFUNCTION()
	int GetAndroidPriorityEnumInt();

	/**
	 * Get the Android heading delay value from the Android Heading Delay enum
	 */
	UFUNCTION()
	int GetAndroidHeadingDelayEnumInt();

	/**
	 * Check Android Permissions
	 */
	UFUNCTION()
	bool CheckAndroidPermissions();

	/**
	 * Request Android Permissions
	 */
	UFUNCTION()
	void RequestAndroidPermissions();

	/**
	 * Single Update Requested
	 */
	bool SingleUpdateRequested = false;

	/**
	 *  Start Update Requested
	 */
	bool StartUpdateRequested = false;

	/**
	 * Stop Update Requested
	 */
	bool StopUpdateRequested = false;

	/**
	 * Permissions Being Requested
	 */
	bool PermissionsBeingRequested = false;

	/**
	 * Permissions Handler
	 */
	UGeoAndroidPermissionHandler* PermissionsHandler;

#if PLATFORM_ANDROID
	/* Java JNI */
	JNIEnv* JNIEnv;

	/* Java method to start location updates */
	jmethodID LocationUpdateStart_JavaMethod;

	/* Java method to stop location updates */
	jmethodID LocationUpdateStop_JavaMethod;

	/* Java method to request a single position update */
	jmethodID RequestSinglePositionUpdate_JavaMethod;

	/* Java method to start heading updates */
	jmethodID HeadingUpdateStart_JavaMethod;

	/* Java method to stop heading updates */
	jmethodID HeadingUpdateStop_JavaMethod;

	/* Java method to request a single heading update */
	jmethodID RequestSingleHeadingUpdate_JavaMethod;

	/* Java method to request the device orientation */
	jmethodID GetDeviceOrientation_JavaMethod;

	/* Java method to get magnetic declination */
	jmethodID GetMagneticDeclination_JavaMethod;
#endif

};

/* Static Android Interval Time */
static int AndroidIntervalTime = 1000;

/* Static Android Fastest Interval Time */
static int AndroidFastestIntervalTime = 1000;

/* Static Android Priority */
static EGeoLocationAndroidPriority AndroidPriority = EGeoLocationAndroidPriority::HighAccuracy;

/* Static Android Heading Delay */
static EGeoLocationAndroidHeadingDelay AndroidHeadingDelay = EGeoLocationAndroidHeadingDelay::SensorDelayGame;

/* Static Android Minimum Distance */
static float AndroidMinimumDistance = 0.0f;
