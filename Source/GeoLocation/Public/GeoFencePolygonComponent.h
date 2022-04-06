/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationPosition.h"
#include "GeoLocationComponent.h"
#include "GeoLocationEnums.h"
#include "GeoFenceComponent.h"
#include "GeoFencePolygonComponent.generated.h"

/**
 * Geo Fence Polygon Component
 */
UCLASS(ClassGroup=(GeoLocation), meta=(BlueprintSpawnableComponent))
class GEOLOCATION_API UGeoFencePolygonComponent : public UGeoFenceComponent
{

	GENERATED_BODY()

public:

	/**
	 * Constructor
	 */
	UGeoFencePolygonComponent(const FObjectInitializer& ObjectInitializer);

	/* Points */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	TArray<FGeoCoordinate> PolygonPoints;

	/**
	 * Sets the points for this polygon geo fence
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void SetGeoFencePolygons(TArray<FGeoCoordinate> points);

private:

	/**
	 * Returns if a provided geo location component is inside the geo fence area for this component
	 */
	virtual bool IsGeoLocationInGeoFence(UGeoLocationComponent* geoLocationComponent) override;

};

