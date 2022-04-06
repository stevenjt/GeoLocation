/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#include "GeoFenceComponent.h"

UGeoFenceComponent::UGeoFenceComponent(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
}

void UGeoFenceComponent::BeginPlay()
{
	Index = FGeoLocationModule::Get().GeoFences().Add(this);
	Super::BeginPlay();
}

EGeoFenceEvent UGeoFenceComponent::GetGeoFenceEvent(UGeoLocationComponent* geoLocationComponent)
{
	// Add a false state if this geo location component has not yet been added to the TMap
	if (GeoLocationFenceStates.Find(geoLocationComponent->GetUniqueID()) == nullptr)
	{
		GeoLocationFenceStates.Add(geoLocationComponent->GetUniqueID(), false);
	}

	if (this->IsGeoLocationInGeoFence(geoLocationComponent))
	{
		if (!GeoLocationFenceStates[geoLocationComponent->GetUniqueID()])
		{
			OnGeoFenceBeginOverlap.Broadcast(geoLocationComponent);
			GeoLocationFenceStates.Add(geoLocationComponent->GetUniqueID(), true);
			return EGeoFenceEvent::Begin;
		}
	}
	else
	{
		if (GeoLocationFenceStates[geoLocationComponent->GetUniqueID()])
		{
			OnGeoFenceEndOverlap.Broadcast(geoLocationComponent);
			GeoLocationFenceStates.Add(geoLocationComponent->GetUniqueID(), false);
			return EGeoFenceEvent::End;
		}
	}

	return EGeoFenceEvent::NoChange;
}
