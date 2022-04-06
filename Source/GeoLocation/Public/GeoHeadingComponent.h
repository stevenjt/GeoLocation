/**
 * GeoLocation
 *
 * Copyright (c) 2018 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "GeoHeading.h"
#include "GeoLocationComponent.h"

#include "GeoHeadingComponent.generated.h"

/**
 * Access Heading data for iOS, Android and HTML5
 */
UCLASS(ClassGroup = (GeoLocation), meta = (BlueprintSpawnableComponent))
class GEOLOCATION_API UGeoHeadingComponent : public UActorComponent
{

	GENERATED_BODY()

	/* Heading Update Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHeadingUpdateDelegate, FGeoHeading, heading);

	/* Heading Error Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHeadingErrorDelegate, FString, message);

public:

	/**
	 * Constructor
	 */
	UGeoHeadingComponent(const FObjectInitializer& ObjectInitializer);

	/**
	 * Heading Update Delegate. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FHeadingUpdateDelegate HeadingUpdateDelegate;

	/**
	 * Heading Error Delegate. This can be assigned in Blueprint.
	 */
	UPROPERTY(BlueprintAssignable)
	FHeadingErrorDelegate HeadingErrorDelegate;

	/**
	 * Start position updates
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void StartHeadingUpdates(bool calculateTrueNorth, bool adjustForScreenOrientation);

	/**
	 * Stop position updates
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void StopHeadingUpdates();

	/**
	 * Request single heading update
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void RequestSingleHeadingUpdate();

	/**
	 * Returns if a position update is currently running
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	bool IsRunning();

	/**
	 * Returns the last Geo Location received
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	FGeoHeading GetLastHeading();

	/**
	 * Returns if true north heading is supported on the current platform
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	bool IsTrueNorthHeadingSupportedByPlatform();

	/**
	 * End Play event.
	 */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:

	/* Geo Location Component */
	UPROPERTY()
	UGeoLocationComponent* GeoLocationComponent;

	/* Current Geo Location */
	UPROPERTY()
	UGeoLocationPosition* CurrentLocation = nullptr;

	/* Boolean for if the Heading provider is running */
	UPROPERTY()
	bool Running = false;

	/* Boolean for if a single heading request is running */
	UPROPERTY()
	bool SingleRequestRunning = false;

	/* Last heading received */
	UPROPERTY()
	FGeoHeading LastHeading;

	/* Calculate True North boolean */
	UPROPERTY()
	bool CalculateTrueNorth = false;

	/* Adjust For Screen Orientation boolean */
	UPROPERTY()
	bool AdjustForScreenOrientation = false;

	/* Orientation Modifier */
	float orientationModifier = 0.0f;

	/**
	 * Receives location data as it changes
	 */
	UFUNCTION()
	void LocationUpdate(UGeoLocationPosition* position);

	/**
	 * Add the heading update delegate
	 */
	UFUNCTION()
	void AddHeadingDelegates();

	/**
	 * Remove the heading update delegate
	 */
	UFUNCTION()
	void RemoveHeadingDelegates();

	/**
	 * Called by the provider when a new update is available. This will broadcast to the Heading Update delegate.
	 */
	UFUNCTION()
	void HeadingUpdate(FGeoHeading heading);

	/**
	 * Called by the provider when a heading error occurs. This will broadcast to the Heading Error delegate.
	 */
	UFUNCTION()
	void HeadingError(FString message);

};
