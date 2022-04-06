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
#include "GeoLocationUtilities.h"
#include "GeoFenceRectangleComponent.generated.h"

/**
* Geo Fence Rectangle Component
*/
UCLASS(ClassGroup=(GeoLocation), meta=(BlueprintSpawnableComponent))
class GEOLOCATION_API UGeoFenceRectangleComponent : public UGeoFenceComponent
{

	GENERATED_BODY()

public:

	/**
	 * Constructor
	 */
	UGeoFenceRectangleComponent(const FObjectInitializer& ObjectInitializer);

	/* Rectangle Origin */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	FGeoCoordinate OriginLocation;

	/* Rectangle Width */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Width (Metres)", Category = GeoLocation)
	float WidthMetres;

	/* Rectangle Width */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Height (Metres)", Category = GeoLocation)
	float HeightMetres;

	/**
	 * Sets the points for this rectangle geo fence
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void SetGeoFenceRectangle(FGeoCoordinate origin, float width, float height);

private:

	/**
	 * Returns if a provided geo location component is inside the geo fence area for this component
	 */
	virtual bool IsGeoLocationInGeoFence(UGeoLocationComponent* geoLocationComponent) override;

};

