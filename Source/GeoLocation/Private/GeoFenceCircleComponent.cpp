/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#include "GeoFenceCircleComponent.h"

UGeoFenceCircleComponent::UGeoFenceCircleComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UGeoFenceCircleComponent::SetGeoFenceCircle(FGeoCoordinate origin, float radius)
{
	OriginLocation.Latitude = origin.Latitude;
	OriginLocation.Longitude = origin.Longitude;
	RadiusMetres = radius;
}

bool UGeoFenceCircleComponent::IsGeoLocationInGeoFence(UGeoLocationComponent* geoLocationComponent)
{
	return UGeoLocationUtilities::IsPositionInCircle(geoLocationComponent->GetLastPosition()->GetGeoCoordinateStruct(), OriginLocation, RadiusMetres);
}
