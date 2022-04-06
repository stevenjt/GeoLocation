/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationEnums.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeoLocationSettings.generated.h"

/**
 * Access various Geo Location platform specific settings for iOS, Android and HTML5
 */
UCLASS(config=Engine, defaultconfig)
class GEOLOCATION_API UGeoLocationSettings : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()
	
public:

	/* Android Google Play Services Version Config */
	UPROPERTY(Config)
	FString AndroidGooglePlayServicesVersion;

	/**
	 * Set the Android interval time
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetAndroidIntervalTime(int intervalTime = 1000);

	/**
	 * Set the Android fastest interval time
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetAndroidFastestIntervalTime(int fastestIntervalTime = 1000);

	/**
	 * Set the Android location priority
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetAndroidPriority(EGeoLocationAndroidPriority androidPriority = EGeoLocationAndroidPriority::HighAccuracy);

	/**
	 * Set the Android heading delay
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetAndroidHeadingDelay(EGeoLocationAndroidHeadingDelay headingDelay = EGeoLocationAndroidHeadingDelay::SensorDelayGame);

	/**
	 * Set the Android location minimum distance
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetAndroidMinimumDistance(float minimumDistance = 0.0f);

	/**
	 * Set the HTML5 High Accuracy option
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetHTML5HighAccuracy(bool highAccuracy = true);

	/**
	 * Set the iOS Accuracy
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetIOSAccuracy(EGeoLocationIOSAccuracy accuracy = EGeoLocationIOSAccuracy::Best);

	/**
	 * Set the iOS Minimum Distance
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetIOSMinimumDistance(float minimumDistance = 0.0f);

	/**
	 * Set the editor simulated geo location using a preset
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetEditorSimulatedGeoLocationPreset(EGeoLocationPreset preset);

	/**
	 * Set the editor simulated geo location using custom latitude and longitude values
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetEditorSimulatedGeoLocationCustom(float latitude, float longitude);

	/**
	 * Set the editor simulated heading magnetic north using a custom value
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetEditorSimulatedHeadingMagneticNorthCustom(float magneticNorth);

	/**
	 * Set the editor simulated heading true north using a custom value
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetEditorSimulatedHeadingTrueNorthCustom(float trueNorth);

	/**
	 * Set the editor simulated location update interval time
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetEditorSimulatedIntervalTime(float intervalTime = 1.0f);

	/**
	 * Set the editor simulated heading update interval time
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static void GeoLocationSetEditorSimulatedHeadingIntervalTime(float intervalTime = 1.0f);

};
