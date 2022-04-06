/**
* GeoLocation
*
* Copyright (c) 2017 Steven Thompson
**/

#include "GeoLocationTestsHelper.h"

//// IsPositionInArea Tests

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test1, "GeoLocation.Utilities.IsPositionInArea.Glasgow.GeorgeSquare Position Inside Area #1", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test1::RunTest(const FString& Parameters)
{
	return UGeoLocationUtilities::IsPositionInArea({ 55.860857f, -4.24953f }, GeoLocationTestsHelper::GetGlasgowGeorgeSquarePoints()) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test2, "GeoLocation.Utilities.IsPositionInArea.Glasgow.GeorgeSquare Position Inside Area #2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test2::RunTest(const FString& Parameters)
{
	return UGeoLocationUtilities::IsPositionInArea({ 55.861259f, -4.250721f }, GeoLocationTestsHelper::GetGlasgowGeorgeSquarePoints()) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test3, "GeoLocation.Utilities.IsPositionInArea.Glasgow.GeorgeSquare Position Outside Area", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test3::RunTest(const FString& Parameters)
{
	return UGeoLocationUtilities::IsPositionInArea({ 55.860446f, -4.247856f }, GeoLocationTestsHelper::GetGlasgowGeorgeSquarePoints()) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test4, "GeoLocation.Utilities.IsPositionInArea.Glasgow.GeorgeSquar Position Inside Area #3", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test4::RunTest(const FString& Parameters)
{
	return UGeoLocationUtilities::IsPositionInArea({ 55.861150f, -4.250206f }, GeoLocationTestsHelper::GetGlasgowGeorgeSquarePoints()) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test5, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Inside Area #1", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test5::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 5.0f, 5.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 0.0f, 0.0f });
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 10.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test5_Order2, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Inside Area #1 Order 2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test5_Order2::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 5.0f, 5.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 0.0f, 0.0f });
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 10.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test5_Order2_Outside, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Inside Area #1 Order 2 Outside", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test5_Order2_Outside::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 5.0f, 0.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 0.0f, 0.0f });
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 10.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test5_Order3, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Inside Area #1 Order 3", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test5_Order3::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 5.0f, 5.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 10.0f, 0.0f });
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 0.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test5_Order4, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Inside Area #1 Order 4", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test5_Order4::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 5.0f, 9.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 10.0f, 0.0f });
	areaPoints.Add({ 0.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test5_Order4_Outside, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Inside Area #1 Order 4 Outside", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test5_Order4_Outside::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 0.0f, 9.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 10.0f, 0.0f });
	areaPoints.Add({ 0.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test5_Order5, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Inside Area #1 Order 5", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test5_Order5::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 5.0f, 5.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 0.0f, 0.0f });
	areaPoints.Add({ 10.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test5_Order5_Outside, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Inside Area #1 Order 5 Outside", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test5_Order5_Outside::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 10.5f, 5.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 0.0f, 0.0f });
	areaPoints.Add({ 10.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test6, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare1 Position Outside Area", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test6::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 15.0f, 15.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ 0.0f, 0.0f });
	areaPoints.Add({ 0.0f, 10.0f });
	areaPoints.Add({ 10.0f, 10.0f });
	areaPoints.Add({ 10.0f, 0.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test7, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare2 Position Inside Area #2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test7::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ 10.0f, 10.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ -15.0f, -15.0f });
	areaPoints.Add({ -15.0f,  15.0f });
	areaPoints.Add({ 15.0f, 15.0f });
	areaPoints.Add({ 15.0f, -15.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test8, "GeoLocation.Utilities.IsPositionInArea.General.GeometrySquare2 Position Outside Area #3", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test8::RunTest(const FString& Parameters)
{
	FGeoCoordinate currentPosition{ -16.0f, 15.0f };

	TArray<FGeoCoordinate> areaPoints;
	areaPoints.Add({ -15.0f, -15.0f });
	areaPoints.Add({ -15.0f,  15.0f });
	areaPoints.Add({ 15.0f, 15.0f });
	areaPoints.Add({ 15.0f, -15.0f });

	return UGeoLocationUtilities::IsPositionInArea(currentPosition, areaPoints) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test9, "GeoLocation.Utilities.IsPositionInArea.NewYork.TimesSquare Position Inside Area", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test9::RunTest(const FString& Parameters)
{
	return UGeoLocationUtilities::IsPositionInArea({ 40.758641f, -73.985111f }, GeoLocationTestsHelper::GetNewYorkTimesSquarePoints()) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInArea_Test10, "GeoLocation.Utilities.IsPositionInArea.NewYork.TimesSquare Position Outside Area", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInArea_Test10::RunTest(const FString& Parameters)
{
	return UGeoLocationUtilities::IsPositionInArea({ 40.758044f, -73.983770f }, GeoLocationTestsHelper::GetNewYorkTimesSquarePoints()) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_GetGeoFenceRectangle_Test1, "GeoLocation.Utilities.GetGeoFenceRectangle Width and Height Check #1", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_GetGeoFenceRectangle_Test1::RunTest(const FString& Parameters)
{
	float width = 200.0f;
	float height = 200.0f;

	TArray<FGeoCoordinate> rectanglePoints = UGeoLocationUtilities::GetGeoFenceRectangle({ 55.860857f, -4.24953f }, width, height);

	float widthDistanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(rectanglePoints[1], rectanglePoints[2]) * 1000;
	float heightDistanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(rectanglePoints[0], rectanglePoints[1]) * 1000;

	bool distanceWidthNearGiven = GeoLocationTestsHelper::CompareFloats(widthDistanceMetres, width, 1.0f);
	bool distanceHeightNearGiven = GeoLocationTestsHelper::CompareFloats(heightDistanceMetres, height, 1.0f);

	return distanceWidthNearGiven && distanceHeightNearGiven;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_GetGeoFenceRectangle_Test2, "GeoLocation.Utilities.GetGeoFenceRectangle Width and Height Check #2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_GetGeoFenceRectangle_Test2::RunTest(const FString& Parameters)
{
	float width = 220.0f;
	float height = 1000.0f;

	TArray<FGeoCoordinate> rectanglePoints = UGeoLocationUtilities::GetGeoFenceRectangle({ 55.860857f, -4.24953f }, width, height);

	float widthDistanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(rectanglePoints[1], rectanglePoints[2]) * 1000;
	float heightDistanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(rectanglePoints[0], rectanglePoints[1]) * 1000;

	bool distanceWidthNearGiven = GeoLocationTestsHelper::CompareFloats(widthDistanceMetres, width, 1.0f);
	bool distanceHeightNearGiven = GeoLocationTestsHelper::CompareFloats(heightDistanceMetres, height, 1.0f);

	return distanceWidthNearGiven && distanceHeightNearGiven;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_GetGeoFenceRectangle_Test3, "GeoLocation.Utilities.GetGeoFenceRectangle Width and Height Check #3", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_GetGeoFenceRectangle_Test3::RunTest(const FString& Parameters)
{
	float width = 2500.0f;
	float height = 2500.0f;

	TArray<FGeoCoordinate> rectanglePoints = UGeoLocationUtilities::GetGeoFenceRectangle({ 55.860857f, -4.24953f }, width, height);

	float widthDistanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(rectanglePoints[1], rectanglePoints[2]) * 1000;
	float heightDistanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(rectanglePoints[0], rectanglePoints[1]) * 1000;

	bool distanceWidthNearGiven = GeoLocationTestsHelper::CompareFloats(widthDistanceMetres, width, 1.0f);
	bool distanceHeightNearGiven = GeoLocationTestsHelper::CompareFloats(heightDistanceMetres, height, 1.0f);

	return distanceWidthNearGiven && distanceHeightNearGiven;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_GetGeoFenceRectangle_Test4, "GeoLocation.Utilities.GetGeoFenceRectangle Width and Height Check (Random)", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_GetGeoFenceRectangle_Test4::RunTest(const FString& Parameters)
{
	float width = FMath::FRand() * 2500.0f;
	float height = FMath::FRand() * 2500.0f;

	TArray<FGeoCoordinate> rectanglePoints = UGeoLocationUtilities::GetGeoFenceRectangle({ 55.860857f, -4.24953f }, width, height);

	float widthDistanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(rectanglePoints[1], rectanglePoints[2]) * 1000;
	float heightDistanceMetres = UGeoLocationUtilities::CalculateDistanceBetween(rectanglePoints[0], rectanglePoints[1]) * 1000;

	bool distanceWidthNearGiven = GeoLocationTestsHelper::CompareFloats(widthDistanceMetres, width, 1.0f);
	bool distanceHeightNearGiven = GeoLocationTestsHelper::CompareFloats(heightDistanceMetres, height, 1.0f);

	return distanceWidthNearGiven && distanceHeightNearGiven;
}

/** IsPositionInCircle Tests **/

// Basic Usage

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInCircle_Test1, "GeoLocation.Utilities.IsPositionInCircle Position Inside", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInCircle_Test1::RunTest(const FString& Parameters)
{
	FGeoCoordinate circleOrigin = { 55.861259f, -4.250721f };
	float circleRadius = 100.0f;
	FGeoCoordinate position = UGeoLocationUtilities::CalculatePositionOffset(circleOrigin, 50, 0);

	return (UGeoLocationUtilities::IsPositionInCircle(position, circleOrigin, circleRadius)) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInCircle_Test2, "GeoLocation.Utilities.IsPositionInCircle Position Outside", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInCircle_Test2::RunTest(const FString& Parameters)
{
	FGeoCoordinate circleOrigin = { 55.861259f, -4.250721f };
	float circleRadius = 100.0f;
	FGeoCoordinate position = UGeoLocationUtilities::CalculatePositionOffset(circleOrigin, 150, 0);

	return (UGeoLocationUtilities::IsPositionInCircle(position, circleOrigin, circleRadius)) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInCircle_Test3, "GeoLocation.Utilities.IsPositionInCircle Position At Centre", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInCircle_Test3::RunTest(const FString& Parameters)
{
	FGeoCoordinate circleOrigin = { 55.861259f, -4.250721f };
	float circleRadius = 100.0f;
	FGeoCoordinate position = circleOrigin;

	return (UGeoLocationUtilities::IsPositionInCircle(position, circleOrigin, circleRadius)) == true;
}

// Bounds checks

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInCircle_Test4, "GeoLocation.Utilities.IsPositionInCircle Position Near Boundary", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInCircle_Test4::RunTest(const FString& Parameters)
{
	FGeoCoordinate circleOrigin = { 55.861259f, -4.250721f };
	float circleRadius = 100.0f;
	FGeoCoordinate position = UGeoLocationUtilities::CalculatePositionOffset(circleOrigin, circleRadius - 0.1f, 0);

	return (UGeoLocationUtilities::IsPositionInCircle(position, circleOrigin, circleRadius)) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInCircle_Test5, "GeoLocation.Utilities.IsPositionInCircle Position On Boundary", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInCircle_Test5::RunTest(const FString& Parameters)
{
	FGeoCoordinate circleOrigin = { 55.861259f, -4.250721f };
	float circleRadius = 100.0f;
	FGeoCoordinate position = UGeoLocationUtilities::CalculatePositionOffset(circleOrigin, circleRadius, 0);

	return (UGeoLocationUtilities::IsPositionInCircle(position, circleOrigin, circleRadius)) == false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInCircle_Test6, "GeoLocation.Utilities.IsPositionInCircle Position Past Boundary", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInCircle_Test6::RunTest(const FString& Parameters)
{
	FGeoCoordinate circleOrigin = { 55.861259f, -4.250721f };
	float circleRadius = 100.0f;
	FGeoCoordinate position = UGeoLocationUtilities::CalculatePositionOffset(circleOrigin, circleRadius + 0.1f , 0);

	return (UGeoLocationUtilities::IsPositionInCircle(position, circleOrigin, circleRadius)) == false;
}

// Random checks

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInCircle_Test7, "GeoLocation.Utilities.IsPositionInCircle Random Position Inside Radius", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInCircle_Test7::RunTest(const FString& Parameters)
{
	FGeoCoordinate circleOrigin = { 55.861259f, -4.250721f };
	float circleRadius = 100.0f;
	float randomX = FMath::RandRange(-1 * circleRadius / 2.0f, circleRadius / 2.0f);
	float randomY = FMath::RandRange(-1 * circleRadius / 2.0f, circleRadius / 2.0f);
	FGeoCoordinate position = UGeoLocationUtilities::CalculatePositionOffset(circleOrigin, randomX, randomY);

	return (UGeoLocationUtilities::IsPositionInCircle(position, circleOrigin, circleRadius)) == true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGeoLocation_IsPositionInCircle_Test8, "GeoLocation.Utilities.IsPositionInCircle Random Position Outside Radius", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FGeoLocation_IsPositionInCircle_Test8::RunTest(const FString& Parameters)
{
	FGeoCoordinate circleOrigin = { 55.861259f, -4.250721f };
	float circleRadius = 100.0f;
	float randomX = FMath::RandRange(circleRadius + 1.0f, circleRadius + 50.0f);
	float randomY = FMath::RandRange(circleRadius + 1.0f, circleRadius + 50.0f);
	FGeoCoordinate position = UGeoLocationUtilities::CalculatePositionOffset(circleOrigin, randomX, randomY);

	return (UGeoLocationUtilities::IsPositionInCircle(position, circleOrigin, circleRadius)) == false;
}
