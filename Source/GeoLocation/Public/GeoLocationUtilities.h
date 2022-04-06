/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationPosition.h"
#include "GeoLocationEnums.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeoLocationUtilities.generated.h"

/**
 * Utility function library
 */
UCLASS()
class GEOLOCATION_API UGeoLocationUtilities : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:

	/**
	 * Calculate the distance between two locations
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static float CalculateDistanceBetween(FGeoCoordinate position1, FGeoCoordinate position2);

	/**
	 * Calculate an offset position using east and north offset values (metres). Negative offsets allow west and south offsets.
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static FGeoCoordinate CalculatePositionOffset(FGeoCoordinate position, float offsetEast, float offsetNorth);

	/**
	 * Get a geo fence rectangle based on the provided origin location, width and height
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static TArray<FGeoCoordinate> GetGeoFenceRectangle(FGeoCoordinate origin, float widthMetres, float heightMetres);

	/**
	 * Returns if a position is inside the circle given the origin position and radius
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static bool IsPositionInCircle(FGeoCoordinate position, FGeoCoordinate circleOrigin, float circleRadiusMetres);

	/**
	 * Returns if a position is inside the area of the given position TArray
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	static bool IsPositionInArea(FGeoCoordinate position, TArray<FGeoCoordinate> areaPoints);

};
