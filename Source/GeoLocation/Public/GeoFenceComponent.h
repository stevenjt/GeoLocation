/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocation.h"
#include "GeoLocationPosition.h"
#include "GeoLocationEnums.h"
#include "Components/ActorComponent.h"
#include "GeoFenceComponent.generated.h"

/**
* Geo Fence Component
*/
UCLASS(Abstract, ClassGroup=(GeoLocation), meta=(BlueprintSpawnableComponent))
class GEOLOCATION_API UGeoFenceComponent : public UActorComponent
{

	GENERATED_BODY()

	/* On Geo Fence Begin Overlap Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGeoFenceBeginOverlap, UGeoLocationComponent*, geoLocationComponent);

	/* On Geo Fence End Overlap Delegate definition */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGeoFenceEndOverlap, UGeoLocationComponent*, geoLocationComponent);

public:

	/**
	 * Constructor
	 */
	UGeoFenceComponent(const FObjectInitializer& ObjectInitializer);

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
	 * Begin Play event
	 */
	UFUNCTION()
	virtual void BeginPlay() override;

	/**
	 * Get the geo fence event based on the provided geo location component
	 */
	UFUNCTION()
	EGeoFenceEvent GetGeoFenceEvent(UGeoLocationComponent* geoLocationComponent);

protected:

	/* Array Index for this geo fence in the GeoFences static array in the GeoLocation module */
	UPROPERTY()
	int32 Index;

	/* TMap of the current states of geo location components with this geo fence */
	UPROPERTY()
	TMap<uint32, bool> GeoLocationFenceStates;

private:

	/**
	 * Returns if a provided geo location component is inside the geo fence area for this component. This should be implemented by derived geo fence types.
	 */
	UFUNCTION()
	virtual bool IsGeoLocationInGeoFence(UGeoLocationComponent* geoLocationComponent) PURE_VIRTUAL(UGeoFenceCalculation, return false;);

};
