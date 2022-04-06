/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationUtilities.h"
#include "Misc/AutomationTest.h"

/**
 * Helper class for tests
 */
class GeoLocationTestsHelper
{

public:

	/**
	 * Glasgow George Square geo coordinates
	 */
	static TArray<FGeoCoordinate> GetGlasgowGeorgeSquarePoints()
	{
		TArray<FGeoCoordinate> areaPoints;
		areaPoints.Add({ 55.861706f, -4.251259f });
		areaPoints.Add({ 55.861427f, -4.2489f });
		areaPoints.Add({ 55.860645f, -4.249176f });
		areaPoints.Add({ 55.860916f, -4.251558f });

		return areaPoints;
	}

	/**
	 * New York Times Square geo coordinates
	 */
	static TArray<FGeoCoordinate> GetNewYorkTimesSquarePoints()
	{
		TArray<FGeoCoordinate> areaPoints;
		areaPoints.Add({ 40.756834f, -73.986839f });
		areaPoints.Add({ 40.756440f, -73.985868f });
		areaPoints.Add({ 40.759096f, -73.984333f });
		areaPoints.Add({ 40.759519f, -73.985417f });

		return areaPoints;
	}

	/**
	 * Compare two floating point values, returns if they are within the provided difference from each other
	 */
	static bool CompareFloats(float value1, float value2, float difference)
	{
		return (value1 - value2) <= difference && (value1 - value2) >= -1 * difference;
	}

};
