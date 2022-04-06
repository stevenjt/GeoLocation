/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#include "GeoFencePolygonComponent.h"

UGeoFencePolygonComponent::UGeoFencePolygonComponent(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

void UGeoFencePolygonComponent::SetGeoFencePolygons(TArray<FGeoCoordinate> points)
{
	PolygonPoints.Empty();

	for (int i = 0; i < points.Num(); i++)
	{
		PolygonPoints.Add(points[i]);
	}
}

bool UGeoFencePolygonComponent::IsGeoLocationInGeoFence(UGeoLocationComponent* geoLocationComponent)
{
	return UGeoLocationUtilities::IsPositionInArea(geoLocationComponent->GetLastPosition()->GetGeoCoordinateStruct(), PolygonPoints);
}
