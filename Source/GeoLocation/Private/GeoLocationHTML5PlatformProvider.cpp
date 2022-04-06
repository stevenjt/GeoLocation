/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#include "GeoLocationHTML5PlatformProvider.h"

#if defined PLATFORM_HTML5 && PLATFORM_HTML5
extern "C"
{
	void EMSCRIPTEN_KEEPALIVE GeoLocation_LocationUpdate(double latitude, double longitude, double elevation, double horizontalAccuracy, double verticalAccuracy, double bearing, double speed, long time)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FGeoLocationModule::Get().GetPlatformProvider()->LocationUpdateDelegate.Broadcast(latitude, longitude, elevation, horizontalAccuracy, verticalAccuracy, bearing, speed, time);
		});
	}

	void EMSCRIPTEN_KEEPALIVE GeoLocation_LocationError(char* message, int code)
	{
		FString errorMessage = FString(ANSI_TO_TCHAR(message));
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FGeoLocationModule::Get().GetPlatformProvider()->LocationErrorDelegate.Broadcast(errorMessage, code);
		});
	}

	void EMSCRIPTEN_KEEPALIVE GeoLocation_HeadingUpdate(double magneticNorth, bool calibrated)
	{
		FGeoHeading heading;
		heading.MagneticNorth = magneticNorth;
		heading.TrueNorth = magneticNorth;
		heading.Calibrated = calibrated;

		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FGeoLocationModule::Get().GetPlatformProvider()->HeadingUpdateDelegate.Broadcast(heading);
		});
	}

	void EMSCRIPTEN_KEEPALIVE GeoLocation_HeadingError(char* message)
	{
		FString errorMessage = FString(ANSI_TO_TCHAR(message));
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FGeoLocationModule::Get().GetPlatformProvider()->HeadingErrorDelegate.Broadcast(errorMessage);
		});
	}
}
#endif

void AGeoLocationHTML5PlatformProvider::Setup(UWorld* validWorld)
{
	Super::Setup(validWorld);

#if defined PLATFORM_HTML5 && PLATFORM_HTML5
	EM_ASM(
		/* Location Update function watch Id, used for clearing any current location watches */
		window.GeoLocation_LocationUpdateId = 0;

		/* Boolean for if the position is being watched */
		window.GeoLocation_LocationUpdateRunning = false;

		/* Last location received from watch position */
		window.GeoLocation_LastUpdateLocation = null;

		/* Heading Update function watch Id, used for clearing any current heading watches */
		window.GeoLocation_HeadingUpdateId = 0;

		/* Boolean for if the heading is being watched */
		window.GeoLocation_HeadingUpdateRunning = false;

		/* Boolean for if the single heading is running */
		window.GeoLocation_SingleHeadingUpdateRunning = false;

		/* Boolean for if heading is calibrated */
		window.GeoLocation_HeadingCalibrated = true;

		/* Send Location Update function that is used for both watchPosition and getCurrentPosition calls */
		window.GeoLocation_SendLocationUpdate = function(location)
		{
			var latitude = location.coords.latitude;
			var longitude = location.coords.longitude;
			var elevation = location.coords.altitude || 0.0;
			var horizontalAccuracy = location.coords.accuracy;
			var verticalAccuracy = location.altitudeAccuracy || 0.0;
			var bearing = location.heading || 0.0;
			var speed = location.speed || 0.0;

			_GeoLocation_LocationUpdate(latitude, longitude, elevation, horizontalAccuracy, verticalAccuracy, bearing, speed);

			window.GeoLocation_LastUpdateLocation = location;
		};

		/* Send Location Error function that is used for both watchPosition and getCurrentPosition calls */
		window.GeoLocation_SendLocationError = function(error)
		{
			var errorMessagePtr = allocate(intArrayFromString(error.message), 'i8', ALLOC_NORMAL);
			_GeoLocation_LocationError(errorMessagePtr, error.code);
			_free(errorMessagePtr);
		};

		/* Send Heading Update function */
		window.GeoLocation_SendHeadingUpdate = function(deviceOrientationEvent)
		{
			if (!deviceOrientationEvent.absolute)
			{
				var errorMessagePtr = allocate(intArrayFromString("Absolute heading not available"), 'i8', ALLOC_NORMAL);
				_GeoLocation_HeadingError(errorMessagePtr);
				_free(errorMessagePtr);

				return;
			}

			var heading = 360 - (deviceOrientationEvent.hasOwnProperty("webkitCompassHeading") ? deviceOrientationEvent.webkitCompassHeading : deviceOrientationEvent.alpha);

			_GeoLocation_HeadingUpdate(heading, window.GeoLocation_HeadingCalibrated);

			if (window.GeoLocation_SingleHeadingUpdateRunning)
			{
				window.GeoLocation_SingleHeadingUpdateRunning = false;

				if (!window.GeoLocation_HeadingUpdateRunning)
				{
					window.removeEventListener("deviceorientationabsolute" in window ? "deviceorientationabsolute" : "deviceorientation", window.GeoLocation_SendHeadingUpdate);
				}
			}
		};
	);
#endif
}

void AGeoLocationHTML5PlatformProvider::StartPositionUpdate()
{
#if defined PLATFORM_HTML5 && PLATFORM_HTML5
	EM_ASM_({
		window.GeoLocation_LocationUpdateRunning = true;

		// Clear any current location update that is running before starting one
		navigator.geolocation.clearWatch(window.GeoLocation_LocationUpdateId);

		// Set the high accuracy option
		var watchPositionOptions = {
			enableHighAccuracy: $0
		};

		window.GeoLocation_LocationUpdateId = navigator.geolocation.watchPosition(
			window.GeoLocation_SendLocationUpdate,
			window.GeoLocation_SendLocationError,
			watchPositionOptions);
	}, HTML5HighAccuracy);
#endif
}

void AGeoLocationHTML5PlatformProvider::StopPositionUpdate()
{
#if defined PLATFORM_HTML5 && PLATFORM_HTML5
	EM_ASM(
		window.GeoLocation_LocationUpdateRunning = false;

		navigator.geolocation.clearWatch(window.GeoLocation_LocationUpdateId);
	);
#endif
}

void AGeoLocationHTML5PlatformProvider::RequestSinglePositionUpdate()
{
#if defined PLATFORM_HTML5 && PLATFORM_HTML5
	EM_ASM(
		// When a watch location is running getCurrentPosition does not appear to work. Only use it if watchPosition is not running
		if (!window.GeoLocation_LocationUpdateRunning)
		{
			// Set the high accuracy option
			var watchPositionOptions = {
				enableHighAccuracy: window.GeoLocation_HighAccuracy
			};

			navigator.geolocation.getCurrentPosition(
				window.GeoLocation_SendLocationUpdate,
				window.GeoLocation_SendLocationError,
				watchPositionOptions);
		}
		else
		{
			if (window.GeoLocation_LastUpdateLocation !== null)
			{
				// Use the last cached location from a watchPosition if it is running
				window.GeoLocation_SendLocationUpdate(window.GeoLocation_LastUpdateLocation);
			}
			else
			{
				var errorMessagePtr = allocate(intArrayFromString("Location could not be returned"), 'i8', ALLOC_NORMAL);
				_GeoLocation_LocationError(errorMessagePtr, 2);
				_free(errorMessagePtr);
			}
		}
	);
#endif
}

void AGeoLocationHTML5PlatformProvider::StartHeadingUpdate()
{
#if defined PLATFORM_HTML5 && PLATFORM_HTML5
	EM_ASM(
		window.GeoLocation_HeadingUpdateRunning = true;

		window.addEventListener("deviceorientationabsolute" in window ? "deviceorientationabsolute" : "deviceorientation", window.GeoLocation_SendHeadingUpdate);
	);
#endif
}

void AGeoLocationHTML5PlatformProvider::StopHeadingUpdate()
{
#if defined PLATFORM_HTML5 && PLATFORM_HTML5
	EM_ASM(
		window.GeoLocation_HeadingUpdateRunning = false;

		window.removeEventListener("deviceorientationabsolute" in window ? "deviceorientationabsolute" : "deviceorientation", window.GeoLocation_SendHeadingUpdate);
	);
#endif
}

void AGeoLocationHTML5PlatformProvider::RequestSingleHeadingUpdate()
{
#if defined PLATFORM_HTML5 && PLATFORM_HTML5
	EM_ASM(
		window.GeoLocation_SingleHeadingUpdateRunning = true;

		if (!window.GeoLocation_HeadingUpdateRunning)
		{
			window.addEventListener("deviceorientation", window.GeoLocation_SendHeadingUpdate);
		}
	);
#endif
}

EGeoLocationDeviceOrientation AGeoLocationHTML5PlatformProvider::GetDeviceOrientation()
{
	return Orientation;
}

bool AGeoLocationHTML5PlatformProvider::IsTrueNorthHeadingSupportedByPlatform()
{
	return false;
}
