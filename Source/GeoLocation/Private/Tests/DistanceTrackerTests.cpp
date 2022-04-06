/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#include "GeoLocationTestsHelper.h"
#include "GeoDistanceTrackerComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test1, "GeoLocation.GeoDistanceTrackerComponent.DistanceTravelled No Change", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test1::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	distanceTracker->StartDistanceTracking();
	distanceTracker->StopDistanceTracking();

	bool nearZero = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetDistanceTravelled(), 0.0f, 1.0f);

	return nearZero;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test2, "GeoLocation.GeoDistanceTrackerComponent.DistanceTravelled Single Change", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test2::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };
	FGeoCoordinate end = { 55.861427f, -4.2489f };

	float distanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(start, end) * 1000;

	distanceTracker->StartDistanceTracking();
	distanceTracker->LocationUpdate_TestingOnly(start);
	distanceTracker->LocationUpdate_TestingOnly(end);
	distanceTracker->StopDistanceTracking();

	bool nearDistance = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetDistanceTravelled(), distanceMetres, 2.0f);

	return nearDistance;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test3, "GeoLocation.GeoDistanceTrackerComponent.DistanceTravelled 1 to 10 Changes (Random)", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test3::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };
	FGeoCoordinate end = { 55.861706f, -4.247653f };

	float distanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(start, end) * 1000;

	int jumpNumber = (int)FMath::RandRange(1.f, 10.0f);
	float jumpDistance = distanceMetres / jumpNumber;

	distanceTracker->StartDistanceTracking();
	FGeoCoordinate current = start;
	distanceTracker->LocationUpdate_TestingOnly(current);
	for (int i = 0; i < jumpNumber; i++)
	{
		current = UGeoLocationUtilities::CalculatePositionOffset(current, jumpDistance, 0);
		distanceTracker->LocationUpdate_TestingOnly(current);
	}
	distanceTracker->StopDistanceTracking();

	bool nearDistance = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetDistanceTravelled(), distanceMetres, 2.0f);

	return nearDistance;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test4, "GeoLocation.GeoDistanceTrackerComponent.DistanceTravelled 1 to 100 Changes (Random)", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test4::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };
	FGeoCoordinate end = { 55.861706f, -4.247653f };

	float distanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(start, end) * 1000;

	int jumpNumber = (int)FMath::RandRange(1.f, 100.0f);
	float jumpDistance = distanceMetres / jumpNumber;

	distanceTracker->StartDistanceTracking();
	FGeoCoordinate current = start;
	distanceTracker->LocationUpdate_TestingOnly(current);
	for (int i = 0; i < jumpNumber; i++)
	{
		current = UGeoLocationUtilities::CalculatePositionOffset(current, jumpDistance, 0);
		distanceTracker->LocationUpdate_TestingOnly(current);
	}
	distanceTracker->StopDistanceTracking();

	bool nearDistance = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetDistanceTravelled(), distanceMetres, 2.0f);

	return nearDistance;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test5, "GeoLocation.GeoDistanceTrackerComponent.DistanceTravelled 1 to 150 Changes (Random)", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test5::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };
	FGeoCoordinate end = { 55.861706f, -4.247653f };

	float distanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(start, end) * 1000;

	int jumpNumber = (int)FMath::RandRange(1.f, 150.0f);
	float jumpDistance = distanceMetres / jumpNumber;

	distanceTracker->StartDistanceTracking();
	FGeoCoordinate current = start;
	distanceTracker->LocationUpdate_TestingOnly(current);
	for (int i = 0; i < jumpNumber; i++)
	{
		current = UGeoLocationUtilities::CalculatePositionOffset(current, jumpDistance, 0);
		distanceTracker->LocationUpdate_TestingOnly(current);
	}
	distanceTracker->StopDistanceTracking();

	bool nearDistance = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetDistanceTravelled(), distanceMetres, 2.0f);

	return nearDistance;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test6, "GeoLocation.GeoDistanceTrackerComponent.CurrentSpeed 20 km/h", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test6::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };

	float metersTravelled = 5.55;
	int seconds = 1;
	float correctSpeedKMH = 20.0f;

	distanceTracker->StartDistanceTracking();

	FGeoCoordinate current = start;
	FDateTime time = FDateTime::Now();
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	current = UGeoLocationUtilities::CalculatePositionOffset(current, metersTravelled, 0);
	time += FTimespan::FromSeconds(seconds);
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	distanceTracker->StopDistanceTracking();

	bool nearSpeed = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetCurrentSpeed(), correctSpeedKMH, 1.0f);

	return nearSpeed;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test7, "GeoLocation.GeoDistanceTrackerComponent.CurrentSpeed 5 km/h", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test7::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };

	float metersTravelled = 1.38;
	int seconds = 1;
	float correctSpeedKMH = 5.0f;

	distanceTracker->StartDistanceTracking();

	FGeoCoordinate current = start;
	FDateTime time = FDateTime::Now();
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	current = UGeoLocationUtilities::CalculatePositionOffset(current, metersTravelled, 0);
	time += FTimespan::FromSeconds(seconds);
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	distanceTracker->StopDistanceTracking();

	bool nearSpeed = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetCurrentSpeed(), correctSpeedKMH, 1.0f);

	return nearSpeed;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test8, "GeoLocation.GeoDistanceTrackerComponent.CurrentSpeed Random Distance", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test8::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };

	float metersTravelled = FMath::FRandRange(0.1f, 1000.0f);
	int seconds = 25;
	float correctSpeedKMH = ((metersTravelled * (3600.0f)) / 1000.0f) / seconds;

	distanceTracker->StartDistanceTracking();

	FGeoCoordinate current = start;
	FDateTime time = FDateTime::Now();
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	current = UGeoLocationUtilities::CalculatePositionOffset(current, metersTravelled, 0);
	time += FTimespan::FromSeconds(seconds);
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	distanceTracker->StopDistanceTracking();

	bool nearSpeed = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetCurrentSpeed(), correctSpeedKMH, 1.0f);

	return nearSpeed;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test9, "GeoLocation.GeoDistanceTrackerComponent.CurrentSpeed Random Time", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test9::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };

	float metersTravelled = 45;
	int seconds = (int) FMath::FRandRange(1.0f, 100.0f);
	float correctSpeedKMH = ((metersTravelled * (3600.0f)) / 1000.0f) / seconds;

	distanceTracker->StartDistanceTracking();

	FGeoCoordinate current = start;
	FDateTime time = FDateTime::Now();
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	current = UGeoLocationUtilities::CalculatePositionOffset(current, metersTravelled, 0);
	time += FTimespan::FromSeconds(seconds);
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	distanceTracker->StopDistanceTracking();

	bool nearSpeed = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetCurrentSpeed(), correctSpeedKMH, 1.0f);

	return nearSpeed;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GeoLocation_GeoDistanceTrackerComponent_Test10, "GeoLocation.GeoDistanceTrackerComponent.CurrentSpeed Random Distance and Time", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool GeoLocation_GeoDistanceTrackerComponent_Test10::RunTest(const FString& Parameters)
{
	UGeoDistanceTrackerComponent* distanceTracker = NewObject<UGeoDistanceTrackerComponent>();

	FGeoCoordinate start = { 55.861706f, -4.251259f };

	float metersTravelled = FMath::FRandRange(0.1f, 1000.0f);
	int seconds = (int) FMath::FRandRange(1.0f, 100.0f);

	float correctSpeedKMH = ((metersTravelled * (3600.0f)) / 1000.0f) / seconds;

	distanceTracker->StartDistanceTracking();

	FGeoCoordinate current = start;
	FDateTime time = FDateTime::Now();
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	current = UGeoLocationUtilities::CalculatePositionOffset(current, metersTravelled, 0);
	time += FTimespan::FromSeconds(seconds);
	distanceTracker->LocationUpdate_TestingOnly(current, time);

	distanceTracker->StopDistanceTracking();

	bool nearSpeed = GeoLocationTestsHelper::CompareFloats(distanceTracker->GetCurrentSpeed(), correctSpeedKMH, 1.0f);

	return nearSpeed;
}
