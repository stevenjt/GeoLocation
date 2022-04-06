/**
 * GeoLocation
 *
 * Copyright (c) 2018 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoHeading.generated.h"

/**
 * Geo Location Heading struct
 */
USTRUCT(BlueprintType)
struct FGeoHeading
{

	GENERATED_BODY()

	/* Magnetic North */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	float MagneticNorth;

	/* True North */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	float TrueNorth;

	/* Calibrated */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	bool Calibrated;

};
