/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#include "GeoLocationPosition.h"
#include "GeoLocation.h"

float UGeoLocationPosition::GetLatitude()
{
	return GeoCoordinate.Latitude;
}

float UGeoLocationPosition::GetLongitude()
{
	return GeoCoordinate.Longitude;
}

float UGeoLocationPosition::GetElevation()
{
	return Elevation;
}

float UGeoLocationPosition::GetHorizontalAccuracy()
{
	return HorizontalAccuracy;
}

float UGeoLocationPosition::GetVerticalAccuracy()
{
	return VerticalAccuracy;
}

float UGeoLocationPosition::GetBearing()
{
	return Bearing;
}

float UGeoLocationPosition::GetSpeed()
{
	return Speed;
}

int64 UGeoLocationPosition::GetTime()
{
	return Time;
}

FDateTime UGeoLocationPosition::GetLastUpdated()
{
	return LastUpdated;
}

float UGeoLocationPosition::CalculateDistanceTo(UGeoLocationPosition* targetPosition)
{
	return UGeoLocationUtilities::CalculateDistanceBetween(this->GetGeoCoordinateStruct(), targetPosition->GetGeoCoordinateStruct());
}

FString UGeoLocationPosition::GetLatitudeLongitudeString()
{
	return FString::Printf(TEXT("%f, %f"), GeoCoordinate.Latitude, GeoCoordinate.Longitude);
}

FString UGeoLocationPosition::GetLatitudeLongitudeElevationString()
{
	return FString::Printf(TEXT("%f, %f, %f"), GeoCoordinate.Latitude, GeoCoordinate.Longitude, Elevation);
}

FVector2D UGeoLocationPosition::GenerateVectorForMap(float mapWidth, float mapHeight)
{
	float x = (GetLatitude() + 180) * (mapWidth / 360);
	float y = (90 - GetLongitude()) * (mapHeight / 180);

	return FVector2D(x, y);
}

FVector UGeoLocationPosition::GenerateVectorForSphere(float radius)
{
	double phi = (90 - GetLatitude()) * (PI / 180);
	double theta = (GetLongitude() + 180) * (PI / 180);

	float x = -(radius * FMath::Sin(phi) * FMath::Cos(theta));
	float y = radius * FMath::Cos(phi);
	float z = radius * FMath::Sin(phi) * FMath::Sin(theta);
	
	// Return the coordinates in the right format to match the Unreal coordinate system
	return FVector(-z, x, y);
}

void UGeoLocationPosition::SetLocation(double latitude, double longitude, double elevation)
{
	GeoCoordinate.Latitude = latitude;
	GeoCoordinate.Longitude = longitude;
	Elevation = elevation;

	LastUpdated = FDateTime::Now();
}

void UGeoLocationPosition::SetLocation(FGeoCoordinate position)
{
	GeoCoordinate.Latitude = position.Latitude;
	GeoCoordinate.Longitude = position.Longitude;

	LastUpdated = FDateTime::Now();
}

void UGeoLocationPosition::SetUpdatedTime(FDateTime time)
{
	LastUpdated = time;
}

void UGeoLocationPosition::SetAccuracy(double horizontalAccuracy, double verticalAccuracy)
{
	HorizontalAccuracy = horizontalAccuracy;
	VerticalAccuracy = verticalAccuracy;
}

void UGeoLocationPosition::SetBearing(double bearing)
{
	Bearing = bearing;
}

void UGeoLocationPosition::SetSpeed(double speed)
{
	Speed = speed;
}

void UGeoLocationPosition::SetTime(int64 time)
{
	Time = time;
}

FGeoCoordinate UGeoLocationPosition::GetGeoCoordinateStruct()
{
	FGeoCoordinate position;
	position.Latitude = this->GetLatitude();
	position.Longitude = this->GetLongitude();

	return position;
}
