/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#include "GeoFenceRectangleComponent.h"

UGeoFenceRectangleComponent::UGeoFenceRectangleComponent(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

void UGeoFenceRectangleComponent::SetGeoFenceRectangle(FGeoCoordinate origin, float width, float height)
{
	OriginLocation = origin;
	WidthMetres = width;
	HeightMetres = height;
}

bool UGeoFenceRectangleComponent::IsGeoLocationInGeoFence(UGeoLocationComponent* geoLocationComponent)
{
	return UGeoLocationUtilities::IsPositionInArea(geoLocationComponent->GetLastPosition()->GetGeoCoordinateStruct(),
		UGeoLocationUtilities::GetGeoFenceRectangle(OriginLocation, WidthMetres, HeightMetres));
}
