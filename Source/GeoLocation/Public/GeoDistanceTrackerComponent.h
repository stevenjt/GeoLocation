/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationComponent.h"
#include "GeoDistanceTrackerComponent.generated.h"

#define MAXIMUM_SPEED_KPH 45

#define MINIMUM_SPEED_KPH 4

/**
 * Geo Distance Tracker Component
 */
UCLASS(ClassGroup=(GeoLocation), meta=(BlueprintSpawnableComponent))
class GEOLOCATION_API UGeoDistanceTrackerComponent : public UActorComponent
{

	GENERATED_BODY()

	/* Distance Travelled Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDistanceTravelledUpdate, float, distanceTravelled);

	/* Speed Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpeedUpdate, float, speed);

	/* Error Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FError, FString, message);

public:

	/**
	 * Constructor
	 */
	UGeoDistanceTrackerComponent(const FObjectInitializer& ObjectInitializer);

	/**
	 * Distance Travelled Update Delegate. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FDistanceTravelledUpdate DistanceTravelledUpdate;

	/**
	 * Speed Update Delegate. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FSpeedUpdate SpeedUpdate;

	/**
	 * Error Delegate. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FError ErrorUpdate;

	/* Maximum Valid Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	bool UseSpeedLimits = true;

	/* Maximum Valid Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Maximum Valid Speed (km/h)", Category = GeoLocation, meta = (EditCondition = "UseSpeedLimits"))
	float MaximumValidSpeed = MAXIMUM_SPEED_KPH;

	/* Minimum Valid Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Minimum Valid Speed (km/h)", Category = GeoLocation, meta = (EditCondition = "UseSpeedLimits"))
	float MinimumValidSpeed = MINIMUM_SPEED_KPH;

	/**
	 * Start distance tracking
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void StartDistanceTracking();

	/**
	 * Stop distance tracking
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void StopDistanceTracking();

	/**
	 * Returns the distance travelled
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetDistanceTravelled();

	/**
	 * Return the current speed
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetCurrentSpeed();

	/**
	 * Reset distance tracking
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void ResetDistanceTracking();

	/**
	 * Returns if distance tracking is currently running
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	bool IsRunning();

	/**
	 * Testing LocationUpdate function. This should only be used in automation testing
	 */
	void LocationUpdate_TestingOnly(FGeoCoordinate position, FDateTime time = NULL);

private:

	/* Geo Location Component */
	UPROPERTY()
	UGeoLocationComponent* GeoLocationComponent;

	/* Last geo location position */
	UPROPERTY()
	UGeoLocationPosition* LastGeoLocationPosition;

	/* Boolean for if the Geo Distance Tracker Component is running */
	UPROPERTY()
	bool Running = false;

	/* Boolean for if the last geo location position is ready */
	UPROPERTY()
	bool LastGeoLocationPositionReady = false;

	/* Total distance travelled */
	UPROPERTY()
	float DistanceTravelled = 0.0f;

	/* Current Speed */
	UPROPERTY()
	float CurrentSpeed = 0.0f;

	/* Boolean to ignore speed checks for location updates. This should only be used in automation testing */
	bool IgnoreSpeedChecks = false;

	/**
	 * Receives location data as it changes
	 */
	UFUNCTION()
	void LocationUpdate(UGeoLocationPosition* position);

};
