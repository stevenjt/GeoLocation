/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "GeoLocationPosition.h"

#include "GeoLocationComponent.generated.h"

/**
 * Access Geo Location data for iOS, Android and HTML5
 */
UCLASS(ClassGroup=(GeoLocation), meta=(BlueprintSpawnableComponent))
class GEOLOCATION_API UGeoLocationComponent : public UActorComponent
{

	GENERATED_BODY()

	/* Location Update Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLocationUpdateDelegate, UGeoLocationPosition*, position);

	/* Location Error Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLocationErrorDelegate, FString, message, int, code);

	/* On Geo Fence Begin Overlap Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGeoFenceBeginOverlap, UGeoFenceComponent*, geoFenceComponent);

	/* On Geo Fence End Overlap Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGeoFenceEndOverlap, UGeoFenceComponent*, geoFenceComponent);

public:	

	/**
	 * Location Update Delegate. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FLocationUpdateDelegate LocationUpdateDelegate;

	/**
	 * Location Update Delegate. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FLocationErrorDelegate LocationErrorDelegate;

	/**
	 * Geo Fence Begin Overlap. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGeoFenceBeginOverlap OnGeoFenceBeginOverlap;

	/**
	 * Geo Fence End Overlap. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGeoFenceEndOverlap OnGeoFenceEndOverlap;

	/**
	 * Start position updates
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void StartPositionUpdates();

	/**
	 * Stop position updates
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void StopPositionUpdates();

	/**
	 * Request single position update
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void RequestSinglePositionUpdate();

	/**
	 * Returns if a position update is currently running
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	bool IsRunning();

	/**
	 * Returns the last Geo Location received
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	UGeoLocationPosition* GetLastPosition();

	/* Boolean to set if this location component responds to geo fences */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	bool RespondsToGeoFences = false;

	/**
	 * End Play event.
	 */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:

	/* Boolean for if the Geo Location provider is running */
	UPROPERTY()
	bool Running = false;

	/* Boolean for if a single location request is running */
	UPROPERTY()
	bool SingleRequestRunning = false;

	/* Last position received */
	UPROPERTY()
	UGeoLocationPosition* LastPosition;

	/**
	 * Add the location update delegate
	 */
	UFUNCTION()
	void AddLocationDelegates();

	/**
	 * Remove the location update delegate
	 */
	UFUNCTION()
	void RemoveLocationDelegates();

	/**
	 * Called by the provider when a new update is available. This will broadcast to the Location Update delegate.
	 */
	UFUNCTION()
	void LocationUpdate(double latitude, double longitude, double elevation, double horizontalAccuracy, double verticalAccuracy, double bearing, double speed, int64 time);

	/**
	 * Called by the provider when a location error occurs. This will broadcast to the Location Error delegate.
	 */
	UFUNCTION()
	void LocationError(FString message, int code);

};
