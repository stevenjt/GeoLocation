/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#include "GeoLocationIOSPlatformProvider.h"

#if PLATFORM_IOS
/**
 * Interface for the delegate handler class for CLLocationManager
 */
@interface LocationManagerDelegateHandler : NSObject<CLLocationManagerDelegate>

@end

/**
 * Implementation for the delegate handler class for CLLocationManager
 */
@implementation LocationManagerDelegateHandler

/**
 * Handle the CLLocationManagerDelegate didChangeAuthorizationStatus function to start updating the location if authorized
 */
- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status
{
    if (status == kCLAuthorizationStatusRestricted || status == kCLAuthorizationStatusDenied)
    {
        FGeoLocationModule::Get().GetPlatformProvider()->LocationErrorDelegate.Broadcast(![CLLocationManager locationServicesEnabled] ? @"Location services are not enabled in settings" : @"Location services are not authorized", 1);
    }
}

/**
 * Handle the CLLocationManagerDelegate didUpdateLocations function to broadcast the location using the Unreal Location Update delegate
 */
-(void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations
{
	CLLocation* location = [locations lastObject];

    double latitude = location.coordinate.latitude;
    double longitude = location.coordinate.longitude;
    double altitude = location.altitude;
    double horizontalAccuracy = location.horizontalAccuracy;
    double verticalAccuracy = location.verticalAccuracy;
    double course = location.course;
    double speed = location.speed;
    long time = 0;

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
        FGeoLocationModule::Get().GetPlatformProvider()->LocationUpdateDelegate.Broadcast(
            latitude,
            longitude,
            altitude,
            horizontalAccuracy,
            verticalAccuracy,
            course,
            speed,
            time
        );

        ((AGeoLocationIOSPlatformProvider *)FGeoLocationModule::Get().GetPlatformProvider())->LastUpdateLocation = [[CLLocation alloc] initWithCoordinate:CLLocationCoordinate2DMake(latitude, longitude) altitude: altitude horizontalAccuracy: horizontalAccuracy verticalAccuracy: verticalAccuracy course: course speed: speed timestamp: [NSDate dateWithTimeIntervalSince1970: time]];
	});
}

/**
 * Handle the CLLocationManagerDelegate didUpdateHeading function to broadcast the heading using the Unreal Heading Update delegate
 */
-(void)locationManager:(CLLocationManager *)manager didUpdateHeading : (CLHeading *)newHeading
{
	FGeoHeading heading;
	heading.MagneticNorth = (float)newHeading.magneticHeading;
	heading.TrueNorth = (float)newHeading.trueHeading;
	heading.Calibrated = (bool)newHeading.headingAccuracy > 0.0f;

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		FGeoLocationModule::Get().GetPlatformProvider()->HeadingUpdateDelegate.Broadcast(heading);

        if (((AGeoLocationIOSPlatformProvider *)FGeoLocationModule::Get().GetPlatformProvider())->SingleHeadingUpdateRunning)
        {
            ((AGeoLocationIOSPlatformProvider *)FGeoLocationModule::Get().GetPlatformProvider())->SingleHeadingUpdateRunning = false;

            if (!((AGeoLocationIOSPlatformProvider *)FGeoLocationModule::Get().GetPlatformProvider())->HeadingUpdateRunning)
            {
                ((AGeoLocationIOSPlatformProvider *)FGeoLocationModule::Get().GetPlatformProvider())->StopHeadingUpdate();
            }
        }
    });
}

/**
 * Handle the CLLocationManagerDelegate didFailWithError function to broadcast the error using the Unreal Error Update delegate
 */
-(void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
        FGeoLocationModule::Get().GetPlatformProvider()->LocationErrorDelegate.Broadcast(![CLLocationManager locationServicesEnabled] ? @"Location services are not enabled in settings" : @"Location services error", 1);
	});
}

@end

/* Static CLLocationManager instance */
static CLLocationManager* LocationManager;
#endif

void AGeoLocationIOSPlatformProvider::Setup(UWorld* validWorld)
{
	Super::Setup(validWorld);

#if PLATFORM_IOS
	dispatch_async(dispatch_get_main_queue(), ^{
		LocationManager = [[CLLocationManager alloc] init];

		LocationManager.delegate = [[LocationManagerDelegateHandler alloc] init];

		[LocationManager requestWhenInUseAuthorization];
	});
#endif

	FCoreDelegates::ApplicationReceivedScreenOrientationChangedNotificationDelegate.AddUObject(this, &AGeoLocationIOSPlatformProvider::OrientationChangedHandler);
}

void AGeoLocationIOSPlatformProvider::StartPositionUpdate()
{
#if PLATFORM_IOS
	this->LocationUpdateRunning = true;

	dispatch_async(dispatch_get_main_queue(), ^{
		LocationManager.desiredAccuracy = this->GetIOSAccuracy();
		LocationManager.distanceFilter = IOSMinimumDistance;

		[LocationManager startUpdatingLocation];
	});
#endif
}

void AGeoLocationIOSPlatformProvider::StopPositionUpdate()
{
#if PLATFORM_IOS
	this->LocationUpdateRunning = false;

	dispatch_async(dispatch_get_main_queue(), ^{
		[LocationManager stopUpdatingLocation];
	});
#endif
}

void AGeoLocationIOSPlatformProvider::RequestSinglePositionUpdate()
{
#if PLATFORM_IOS
	if (!this->LocationUpdateRunning)
	{
		dispatch_async(dispatch_get_main_queue(), ^{
			[LocationManager requestLocation];
		});
	}
	else
	{
		if (this->LastUpdateLocation != nil)
		{
			// Use the last cached location from startUpdatingLocation if it is running
			CLLocation* location = this->LastUpdateLocation;

			FGeoLocationModule::Get().GetPlatformProvider(this->world)->LocationUpdateDelegate.Broadcast(location.coordinate.latitude, location.coordinate.longitude, location.altitude, location.horizontalAccuracy, location.verticalAccuracy, location.course, location.speed, 0);
		}
		else
		{
			FGeoLocationModule::Get().GetPlatformProvider(this->world)->LocationErrorDelegate.Broadcast(@"Location could not be returned", 1);
		}
	}
#endif
}
void AGeoLocationIOSPlatformProvider::StartHeadingUpdate()
{
#if PLATFORM_IOS
	this->HeadingUpdateRunning = true;

	dispatch_async(dispatch_get_main_queue(), ^{
		[LocationManager startUpdatingHeading];
	});
#endif
}

void AGeoLocationIOSPlatformProvider::StopHeadingUpdate()
{
#if PLATFORM_IOS
	this->HeadingUpdateRunning = false;

	dispatch_async(dispatch_get_main_queue(), ^{
		[LocationManager stopUpdatingHeading];
	});
#endif
}

void AGeoLocationIOSPlatformProvider::RequestSingleHeadingUpdate()
{
#if PLATFORM_IOS
	this->SingleHeadingUpdateRunning = true;

	if (!this->HeadingUpdateRunning)
	{
		dispatch_async(dispatch_get_main_queue(), ^{
			[LocationManager startUpdatingHeading];
		});
	}
#endif
}

EGeoLocationDeviceOrientation AGeoLocationIOSPlatformProvider::GetDeviceOrientation()
{
	return Orientation;
}

#if PLATFORM_IOS
CLLocationAccuracy AGeoLocationIOSPlatformProvider::GetIOSAccuracy()
{
	if (IOSAccuracy == EGeoLocationIOSAccuracy::BestForNavigation)
	{
		return kCLLocationAccuracyBestForNavigation;
	}
	else if (IOSAccuracy == EGeoLocationIOSAccuracy::Best)
	{
		return kCLLocationAccuracyBest;
	}
	else if (IOSAccuracy == EGeoLocationIOSAccuracy::NearestTenMeters)
	{
		return kCLLocationAccuracyNearestTenMeters;
	}
	else if (IOSAccuracy == EGeoLocationIOSAccuracy::HundredMeters)
	{
		return kCLLocationAccuracyHundredMeters;
	}
	else if (IOSAccuracy == EGeoLocationIOSAccuracy::Kilometer)
	{
		return kCLLocationAccuracyKilometer;
	}
	else
	{
		return kCLLocationAccuracyThreeKilometers;
	}
}
#endif

bool AGeoLocationIOSPlatformProvider::IsTrueNorthHeadingSupportedByPlatform()
{
	return true;
}

void AGeoLocationIOSPlatformProvider::OrientationChangedHandler(const int32 orientationRaw)
{
	const EScreenOrientation::Type orientation = static_cast<EScreenOrientation::Type>(orientationRaw);

	switch (orientation)
	{
		case EScreenOrientation::Unknown:
			Orientation = EGeoLocationDeviceOrientation::Unknown;
			break;
		case EScreenOrientation::Portrait:
			Orientation = EGeoLocationDeviceOrientation::Portrait;
			break;
		case EScreenOrientation::PortraitUpsideDown:
			Orientation = EGeoLocationDeviceOrientation::PortraitUpsideDown;
			break;
		case EScreenOrientation::LandscapeLeft:
			Orientation = EGeoLocationDeviceOrientation::LandscapeLeft;
			break;
		case EScreenOrientation::LandscapeRight:
			Orientation = EGeoLocationDeviceOrientation::LandscapeRight;
			break;
	};
}
