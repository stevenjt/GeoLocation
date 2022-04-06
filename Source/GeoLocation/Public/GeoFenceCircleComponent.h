/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationComponent.h"
#include "GeoLocationUtilities.h"
#include "GeoLocationEnums.h"
#include "GeoFenceComponent.h"
#include "GeoFenceCircleComponent.generated.h"

/**
 * Geo Fence Circle Component
 */
UCLASS(ClassGroup=(GeoLocation), meta=(BlueprintSpawnableComponent))
class GEOLOCATION_API UGeoFenceCircleComponent : public UGeoFenceComponent
{

	GENERATED_BODY()

public:

	/**
	 * Constructor
	 */
	UGeoFenceCircleComponent(const FObjectInitializer& ObjectInitializer);

	/* Origin Location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Origin", Category = GeoLocation)
	FGeoCoordinate OriginLocation;

	/* Radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Radius (Metres)", Category = GeoLocation)
	float RadiusMetres = 0;

	/**
	 * Sets the location and radius for this circle geo fence
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void SetGeoFenceCircle(FGeoCoordinate origin, float radius);

private:

	/**
	 * Returns if a provided geo location component is inside the geo fence area for this component
	 */
	virtual bool IsGeoLocationInGeoFence(UGeoLocationComponent* geoLocationComponent) override;

};
