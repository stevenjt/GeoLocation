/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#include "GeoLocationUtilities.h"

// 6371 km is the radius of the Earth
#define EARTH_RADIUS_KM 6371

float UGeoLocationUtilities::CalculateDistanceBetween(FGeoCoordinate position1, FGeoCoordinate position2)
{
	// Distance calculation is implemented using the Haversine formula

	double dLatitude = FMath::DegreesToRadians(position2.Latitude - position1.Latitude);
	double dLongitude = FMath::DegreesToRadians(position2.Longitude - position1.Longitude);

	double a = FMath::Sin(dLatitude / 2) * FMath::Sin(dLatitude / 2) +
		FMath::Cos(FMath::DegreesToRadians(position1.Latitude)) * FMath::Cos(FMath::DegreesToRadians(position2.Latitude)) *
		FMath::Sin(dLongitude / 2) * FMath::Sin(dLongitude / 2);

	double c = 2 * FMath::Atan2(FMath::Sqrt(a), FMath::Sqrt(1 - a));

	double distance = EARTH_RADIUS_KM * c;

	return distance;
}

FGeoCoordinate UGeoLocationUtilities::CalculatePositionOffset(FGeoCoordinate position, float offsetEast, float offsetNorth)
{
	FGeoCoordinate offsetPosition;
	offsetPosition.Latitude = position.Latitude + FMath::RadiansToDegrees((offsetNorth / 1000) / EARTH_RADIUS_KM);
	offsetPosition.Longitude = position.Longitude + FMath::RadiansToDegrees((offsetEast / 1000) / EARTH_RADIUS_KM) / FMath::Cos(FMath::DegreesToRadians(position.Latitude));

	return offsetPosition;
}

TArray<FGeoCoordinate> UGeoLocationUtilities::GetGeoFenceRectangle(FGeoCoordinate origin, float widthMetres, float heightMetres)
{
	TArray<FGeoCoordinate> rectanglePoints;

	float halfWidth = widthMetres / 2;
	float halfHeight = heightMetres / 2;

	rectanglePoints.Add(UGeoLocationUtilities::CalculatePositionOffset(origin, -1 * halfWidth, -1 * halfHeight));
	rectanglePoints.Add(UGeoLocationUtilities::CalculatePositionOffset(origin, -1 * halfWidth, halfHeight));
	rectanglePoints.Add(UGeoLocationUtilities::CalculatePositionOffset(origin, halfWidth, halfHeight));
	rectanglePoints.Add(UGeoLocationUtilities::CalculatePositionOffset(origin, halfWidth, -1 * halfHeight));

	return rectanglePoints;
}

bool UGeoLocationUtilities::IsPositionInCircle(FGeoCoordinate position, FGeoCoordinate circleOrigin, float circleRadiusMetres)
{
	return UGeoLocationUtilities::CalculateDistanceBetween(circleOrigin, position) < (circleRadiusMetres / 1000);
}

bool UGeoLocationUtilities::IsPositionInArea(FGeoCoordinate position, TArray<FGeoCoordinate> areaPoints)
{
	// Currently implemented using ray casting algorithm

	bool positionInArea = false;

	int j = areaPoints.Num() - 1;
	for (int i = 0; i < areaPoints.Num(); i++)
	{
		FGeoCoordinate pointI = areaPoints[i];
		FGeoCoordinate pointJ = areaPoints[j];

		if (((pointI.Longitude > position.Longitude) != (pointJ.Longitude > position.Longitude)) &&
			(position.Latitude < (pointJ.Latitude - pointI.Latitude) * (position.Longitude - pointI.Longitude) / (pointJ.Longitude - pointI.Longitude) + pointI.Latitude))
		{
			positionInArea = !positionInArea;
		}
		j = i;
	}

	return positionInArea;
}
