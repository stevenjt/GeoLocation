/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#include "GeoLocationEditorPlatformProvider.h"

void AGeoLocationEditorPlatformProvider::Setup(UWorld* validWorld)
{
	Super::Setup(validWorld);
}

void AGeoLocationEditorPlatformProvider::StartPositionUpdate()
{
	if (this->world != nullptr)
	{
		this->world->GetTimerManager().SetTimer(this->locationTimerHandle, this, &AGeoLocationEditorPlatformProvider::LocationUpdate, EditorLocationIntervalTime, true);
	}
}

void AGeoLocationEditorPlatformProvider::StopPositionUpdate()
{
	if (this->world != nullptr)
	{
		this->world->GetTimerManager().ClearTimer(this->locationTimerHandle);
	}
}

void AGeoLocationEditorPlatformProvider::RequestSinglePositionUpdate()
{
	this->LocationUpdate();
}

void AGeoLocationEditorPlatformProvider::StartHeadingUpdate()
{
	if (this->world != nullptr)
	{
		this->world->GetTimerManager().SetTimer(this->headingTimerHandle, this, &AGeoLocationEditorPlatformProvider::HeadingUpdate, EditorHeadingIntervalTime, true);
	}
}

void AGeoLocationEditorPlatformProvider::StopHeadingUpdate()
{
	if (this->world != nullptr)
	{
		this->world->GetTimerManager().ClearTimer(this->headingTimerHandle);
	}
}

void AGeoLocationEditorPlatformProvider::RequestSingleHeadingUpdate()
{
	this->HeadingUpdate();
}

EGeoLocationDeviceOrientation AGeoLocationEditorPlatformProvider::GetDeviceOrientation()
{
	return EGeoLocationDeviceOrientation::Portrait;
}

float AGeoLocationEditorPlatformProvider::GetMagneticDeclination(float latitude, float longitude, float altitude, int64 milliseconds)
{
	return EditorSimulatedTrueNorth - EditorSimulatedMagneticNorth;
}

bool AGeoLocationEditorPlatformProvider::IsTrueNorthHeadingSupportedByPlatform()
{
	return true;
}

void AGeoLocationEditorPlatformProvider::LocationUpdate()
{
	FGeoLocationModule::Get().GetPlatformProvider(this->world)->LocationUpdateDelegate.Broadcast(EditorSimulatedPositionLatitude, EditorSimulatedPositionLongitude, EditorSimulatedPositionElevation, 0.0f, 0.0f, 0.0f, 0.0f, 0);
}

void AGeoLocationEditorPlatformProvider::HeadingUpdate()
{
	FGeoHeading heading;
	heading.MagneticNorth = EditorSimulatedMagneticNorth;
	heading.TrueNorth = EditorSimulatedTrueNorth;
	heading.Calibrated = EditorSimulatedHeadingCalibrated;

	FGeoLocationModule::Get().GetPlatformProvider(this->world)->HeadingUpdateDelegate.Broadcast(heading);
}
