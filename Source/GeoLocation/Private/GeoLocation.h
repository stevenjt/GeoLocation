/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "World.h"
#include "UnrealMathUtility.h"
#include "ConfigCacheIni.h"
#include "TimerManager.h"
#include "Resources/Version.h"
#include "Modules/ModuleManager.h"
#include "GeoLocationProvider.h"
#include "GeoFenceComponent.h"

class FGeoLocationModule : public IModuleInterface
{

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	 * Get singleton instance
	 */
	UFUNCTION()
	static FGeoLocationModule& Get();

	/**
	 * Get the Platform Provider
	 */
	UFUNCTION()
	AGeoLocationProvider* GetPlatformProvider(UWorld* world);

	/**
	 * Shutdown the Platform Provider
	 */
	UFUNCTION()
	void ShutdownPlatformProvider();

	/**
	 * Returns the array of active GeoFences
	 */
	UFUNCTION()
	TArray<UGeoFenceComponent*>& GeoFences();

private:

	/**
	 * Add the iOS location when in use description setting to the Plist. This is a required by iOS to access location services.
	 */
	UFUNCTION()
	void AddIOSLocationWhenInUseDescriptionToPlist(FString usageDescription);

	/**
	 * Add the Android Google Play Services version to use to the config. The version to use is based on the current Unreal Engine version.
	 */
	UFUNCTION()
	void AddAndroidGooglePlayServicesVersionConfig();

	/**
	 * Get the Project Default Engine Ini path
	 */
	UFUNCTION()
	FString GetProjectDefaultEngineIniPath();

	/**
	 * World Tick
	 */
	UFUNCTION()
	void WorldTick(UWorld* world, ELevelTick tickType, float deltaTime);

	/* Boolean for if the Geo Location Provider is ready to be used */
	UPROPERTY()
	bool GeoLocationProviderReady = false;

	/* Geo Location Provider */
	UPROPERTY()
	AGeoLocationProvider* GeoLocationProvider;

	/* Active GeoFences array */
	UPROPERTY()
	TArray<UGeoFenceComponent*> _GeoFences;

	/* Boolean for if the GeoFence array is ready to be used */
	UPROPERTY()
	bool GeoFencesReady = false;

};
