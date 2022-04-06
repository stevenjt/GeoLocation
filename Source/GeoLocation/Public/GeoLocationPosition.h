/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "GeoLocationPosition.generated.h"

/**
 * Geographic Coordinate struct
 */
USTRUCT(BlueprintType)
struct FGeoCoordinate
{

	GENERATED_BODY()

	/* Geo Position Latitude */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	float Latitude;

	/* Geo Position Longitude */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeoLocation)
	float Longitude;

};

/**
 * Geographic Location Position
 */
UCLASS(BlueprintType)
class GEOLOCATION_API UGeoLocationPosition : public UObject
{

	GENERATED_BODY()
	
public:

	/**
	 * Returns the latitude for this position
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetLatitude();

	/**
	 * Returns the longitude for this position
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetLongitude();

	/**
	 * Returns the elevation for this position
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetElevation();

	/**
	 * Returns the horizontal accuracy for this position
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetHorizontalAccuracy();

	/**
	 * Returns the vertical accuracy for this position
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetVerticalAccuracy();

	/**
	 * Returns the bearing for this position
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetBearing();

	/**
	 * Returns the speed for this position
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float GetSpeed();

	/**
	 * Get Time
	 */
	int64 GetTime();

	/**
	 * Returns the last updated date & time for this position
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	FDateTime GetLastUpdated();

	/**
	 * Returns the calculated distance from this position to the target position in km
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	float CalculateDistanceTo(UGeoLocationPosition* targetPosition);

	/**
	 * Returns a string of the latitude and longitude of this location
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	FString GetLatitudeLongitudeString();

	/**
	 * Returns a string of the latitude, longitude and elevation of this location
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	FString GetLatitudeLongitudeElevationString();

	/**
	 * Generate a 2D vector for a map
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	FVector2D GenerateVectorForMap(float mapWidth, float mapHeight);

	/**
	 * Generate a 3D vector for a sphere using the provided radius
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	FVector GenerateVectorForSphere(float radius);

	/**
	 * Sets the location for this position using the provided latitude, longitude and elevation
	 */
	void SetLocation(double latitude, double longitude, double elevation);

	/**
	 * Sets the location for this position using a GeoCoordinate struct
	 */
	UFUNCTION(BlueprintCallable, Category = GeoLocation)
	void SetLocation(FGeoCoordinate position);

	/**
	 * Sets the updated time
	 */
	void SetUpdatedTime(FDateTime time);

	/**
	 * Set the horizontal and vertical accuracy
	 */
	UFUNCTION()
	void SetAccuracy(double horizontalAccuracy, double verticalAccuracy);

	/**
	 * Set the bearing
	 */
	UFUNCTION()
	void SetBearing(double bearing);

	/**
	 * Set the speed
	 */
	UFUNCTION()
	void SetSpeed(double speed);

	/**
	 * Set the time
	 */
	void SetTime(int64 time);

	/**
	 * Get this position as a GeoCoordinate struct
	 */
	UFUNCTION()
	FGeoCoordinate GetGeoCoordinateStruct();

private:

	/* Geo Coordinate, contains the Latitude and Longitude */
	UPROPERTY()
	FGeoCoordinate GeoCoordinate;

	/* Geo Location Elevation */
	UPROPERTY()
	double Elevation;

	/* Horizontal Accuracy */
	UPROPERTY()
	double HorizontalAccuracy;

	/* Vertical Accuracy */
	UPROPERTY()
	double VerticalAccuracy;

	/* Bearing */
	UPROPERTY()
	double Bearing;

	/* Speed */
	UPROPERTY()
	double Speed;

	/* Time */
	UPROPERTY()
	int64 Time;

	/* Last Updated date & time */
	UPROPERTY()
	FDateTime LastUpdated;

};
