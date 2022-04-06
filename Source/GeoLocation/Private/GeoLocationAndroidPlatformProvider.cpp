/**
 * GeoLocation
 * 
 * Copyright (c) 2016 Steven Thompson
**/

#include "GeoLocationAndroidPlatformProvider.h"

#if PLATFORM_ANDROID
extern "C"
{
	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_LocationUpdate(JNIEnv* jni, jclass class_, jdouble latitude, jdouble longitude, jdouble elevation, jdouble horizontalAccuracy, jdouble verticalAccuracy, jdouble bearing, jdouble speed, jlong time)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FGeoLocationModule::Get().GetPlatformProvider()->LocationUpdateDelegate.Broadcast(latitude, longitude, elevation, horizontalAccuracy, verticalAccuracy, bearing, speed, time);
		});
	}
}

extern "C"
{
	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_LocationError(JNIEnv* jni, jclass class_)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FGeoLocationModule::Get().GetPlatformProvider()->LocationErrorDelegate.Broadcast("Location Error", -1);
		});
	}
}

extern "C"
{
	JNIEXPORT void Java_com_epicgames_ue4_GameActivity_HeadingUpdate(JNIEnv* jni, jclass class_, jdouble magneticNorth, jboolean calibrated)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			FGeoHeading heading;
			heading.MagneticNorth = (float) magneticNorth;
			heading.Calibrated = (bool) calibrated;

			FGeoLocationModule::Get().GetPlatformProvider()->HeadingUpdateDelegate.Broadcast(heading);
		});
	}
}
#endif

void AGeoLocationAndroidPlatformProvider::Setup(UWorld* validWorld)
{
	Super::Setup(validWorld);

#if PLATFORM_ANDROID
	this->JNIEnv = FAndroidApplication::GetJavaEnv();

	this->LocationUpdateStart_JavaMethod = FJavaWrapper::FindMethod(this->JNIEnv, FJavaWrapper::GameActivityClassID, "UEPluginLocationUpdateStart", "(IIIF)V", false);
	this->LocationUpdateStop_JavaMethod = FJavaWrapper::FindMethod(this->JNIEnv, FJavaWrapper::GameActivityClassID, "UEPluginLocationUpdateStop", "()V", false);
	this->RequestSinglePositionUpdate_JavaMethod = FJavaWrapper::FindMethod(this->JNIEnv, FJavaWrapper::GameActivityClassID, "UEPluginRequestSinglePositionUpdate", "()V", false);

	this->HeadingUpdateStart_JavaMethod = FJavaWrapper::FindMethod(this->JNIEnv, FJavaWrapper::GameActivityClassID, "UEPluginHeadingUpdateStart", "(I)V", false);
	this->HeadingUpdateStop_JavaMethod = FJavaWrapper::FindMethod(this->JNIEnv, FJavaWrapper::GameActivityClassID, "UEPluginHeadingUpdateStop", "()V", false);
	this->RequestSingleHeadingUpdate_JavaMethod = FJavaWrapper::FindMethod(this->JNIEnv, FJavaWrapper::GameActivityClassID, "UEPluginRequestSingleHeadingUpdate", "()V", false);
	this->GetDeviceOrientation_JavaMethod = FJavaWrapper::FindMethod(this->JNIEnv, FJavaWrapper::GameActivityClassID, "UEPluginGetDeviceOrientation", "()I", false);
	this->GetMagneticDeclination_JavaMethod = FJavaWrapper::FindMethod(this->JNIEnv, FJavaWrapper::GameActivityClassID, "UEPluginGetMagneticDeclination", "(FFFJ)F", false);
#endif
}

void AGeoLocationAndroidPlatformProvider::StartPositionUpdate()
{
	if (!this->CheckAndroidPermissions())
	{
		StartUpdateRequested = true;
		return;
	}

#if PLATFORM_ANDROID
	if (!this->LocationUpdateStart_JavaMethod)
	{
		UE_LOG(LogAndroid, Fatal, TEXT("LocationUpdateStart - Not Found"));
		return;
	}

	FJavaWrapper::CallVoidMethod(this->JNIEnv, FJavaWrapper::GameActivityThis, this->LocationUpdateStart_JavaMethod, AndroidIntervalTime, AndroidFastestIntervalTime, this->GetAndroidPriorityEnumInt(), AndroidMinimumDistance);
#endif
}

void AGeoLocationAndroidPlatformProvider::StopPositionUpdate()
{
	if (!this->CheckAndroidPermissions())
	{
		StopUpdateRequested = true;
		return;
	}

#if PLATFORM_ANDROID
	if (!this->LocationUpdateStop_JavaMethod)
	{
		UE_LOG(LogAndroid, Fatal, TEXT("LocationUpdateStop - Not Found"));
		return;
	}

	FJavaWrapper::CallVoidMethod(this->JNIEnv, FJavaWrapper::GameActivityThis, this->LocationUpdateStop_JavaMethod);
#endif
}

void AGeoLocationAndroidPlatformProvider::RequestSinglePositionUpdate()
{
	if (!this->CheckAndroidPermissions())
	{
		SingleUpdateRequested = true;
		return;
	}

#if PLATFORM_ANDROID
	if (!this->RequestSinglePositionUpdate_JavaMethod)
	{
		UE_LOG(LogAndroid, Fatal, TEXT("RequestSinglePositionUpdate - Not Found"));
		return;
	}

	FJavaWrapper::CallVoidMethod(this->JNIEnv, FJavaWrapper::GameActivityThis, this->RequestSinglePositionUpdate_JavaMethod);
#endif
}

void AGeoLocationAndroidPlatformProvider::StartHeadingUpdate()
{
#if PLATFORM_ANDROID
	if (!this->HeadingUpdateStart_JavaMethod)
	{
		UE_LOG(LogAndroid, Fatal, TEXT("HeadingUpdateStart - Not Found"));
		return;
	}

	FJavaWrapper::CallVoidMethod(this->JNIEnv, FJavaWrapper::GameActivityThis, this->HeadingUpdateStart_JavaMethod, this->GetAndroidHeadingDelayEnumInt());
#endif
}

void AGeoLocationAndroidPlatformProvider::StopHeadingUpdate()
{
#if PLATFORM_ANDROID
	if (!this->HeadingUpdateStop_JavaMethod)
	{
		UE_LOG(LogAndroid, Fatal, TEXT("HeadingUpdateStop - Not Found"));
		return;
	}

	FJavaWrapper::CallVoidMethod(this->JNIEnv, FJavaWrapper::GameActivityThis, this->HeadingUpdateStop_JavaMethod);
#endif
}

void AGeoLocationAndroidPlatformProvider::RequestSingleHeadingUpdate()
{
#if PLATFORM_ANDROID
	if (!this->RequestSingleHeadingUpdate_JavaMethod)
	{
		UE_LOG(LogAndroid, Fatal, TEXT("RequestSingleHeadingUpdate - Not Found"));
		return;
	}

	FJavaWrapper::CallVoidMethod(this->JNIEnv, FJavaWrapper::GameActivityThis, this->RequestSingleHeadingUpdate_JavaMethod);
#endif
}

EGeoLocationDeviceOrientation AGeoLocationAndroidPlatformProvider::GetDeviceOrientation()
{
	EGeoLocationDeviceOrientation orientation = EGeoLocationDeviceOrientation::Unknown;
#if PLATFORM_ANDROID
	if (!this->GetDeviceOrientation_JavaMethod)
	{
		UE_LOG(LogAndroid, Fatal, TEXT("GetDeviceOrientation - Not Found"));
		return EGeoLocationDeviceOrientation::Unknown;
	}

	int value = FJavaWrapper::CallIntMethod(this->JNIEnv, FJavaWrapper::GameActivityThis, this->GetDeviceOrientation_JavaMethod);

	if (value == -1)
	{
		orientation = EGeoLocationDeviceOrientation::Unknown;
	}
	else if (value > 330 || value <= 30)
	{
		orientation = EGeoLocationDeviceOrientation::Portrait;
	}
	else if (value > 30 && value <= 120)
	{
		orientation = EGeoLocationDeviceOrientation::LandscapeRight;
	}
	else if (value > 120 && value <= 210)
	{
		orientation = EGeoLocationDeviceOrientation::PortraitUpsideDown;
	}
	else if (value > 210 && value <= 330)
	{
		orientation = EGeoLocationDeviceOrientation::LandscapeLeft;
	}
#endif
	return orientation;
}

#if PLATFORM_ANDROID
jfloat CallFloatMethod(JNIEnv* env, jobject object, jmethodID method, ...)
{
	va_list methodArguments;
	va_start(methodArguments, method);
	jfloat value = env->CallFloatMethodV(object, method, methodArguments);
	va_end(methodArguments);

	return value;
}
#endif

float AGeoLocationAndroidPlatformProvider::GetMagneticDeclination(float latitude, float longitude, float altitude, int64 milliseconds)
{
	float declination = 0.0f;
#if PLATFORM_ANDROID
	if (!this->GetMagneticDeclination_JavaMethod)
	{
		UE_LOG(LogAndroid, Fatal, TEXT("GetMagneticDeclination - Not Found"));
		return false;
	}

	declination = CallFloatMethod(this->JNIEnv, FJavaWrapper::GameActivityThis, this->GetMagneticDeclination_JavaMethod, latitude, longitude, altitude,  milliseconds);
#endif
	return declination;
}

bool AGeoLocationAndroidPlatformProvider::IsTrueNorthHeadingSupportedByPlatform()
{
	return true;
}

int AGeoLocationAndroidPlatformProvider::GetAndroidPriorityEnumInt()
{
	if (AndroidPriority == EGeoLocationAndroidPriority::BalancedPowerAccuracy)
	{
		return 102;
	}
	else if (AndroidPriority == EGeoLocationAndroidPriority::HighAccuracy)
	{
		return 100;
	}
	else if (AndroidPriority == EGeoLocationAndroidPriority::LowPower)
	{
		return 104;
	}
	else
	{
		return 105;
	}
}

int AGeoLocationAndroidPlatformProvider::GetAndroidHeadingDelayEnumInt()
{
	if (AndroidHeadingDelay == EGeoLocationAndroidHeadingDelay::SensorDelayFastest)
	{
		return 0;
	}
	else if (AndroidHeadingDelay == EGeoLocationAndroidHeadingDelay::SensorDelayNormal)
	{
		return 3;
	}
	else if (AndroidHeadingDelay == EGeoLocationAndroidHeadingDelay::SensorDelayUI)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

void AGeoLocationAndroidPlatformProvider::OnPermissionsGranted(const TArray<FString> &permissions, const TArray<bool>& granted)
{
	PermissionsBeingRequested = false;

	for (int32 i = 0; i < permissions.Num(); i++)
	{
		if (granted[i])
		{
			if (SingleUpdateRequested)
			{
				this->RequestSinglePositionUpdate();
				SingleUpdateRequested = false;
			}

			if (StartUpdateRequested)
			{
				this->StartPositionUpdate();
				StartUpdateRequested = false;
			}

			if (StopUpdateRequested)
			{
				this->StopPositionUpdate();
				StopUpdateRequested = false;
			}
		}
		else
		{
			SingleUpdateRequested = false;
			StartUpdateRequested = false;
			StopUpdateRequested = false;

			LocationErrorDelegate.Broadcast("ACCESS_FINE_LOCATION Permission Denied", -1);
		}
	}
}

void AGeoLocationAndroidPlatformProvider::CheckPermissions()
{
	if ((StartUpdateRequested || StopUpdateRequested || SingleUpdateRequested) && !PermissionsBeingRequested)
	{
		this->RequestAndroidPermissions();
	}
}

bool AGeoLocationAndroidPlatformProvider::CheckAndroidPermissions()
{
#if PLATFORM_ANDROID
	return UAndroidPermissionFunctionLibrary::CheckPermission(FString("android.permission.ACCESS_FINE_LOCATION"));
#else
	return true;
#endif
}

void AGeoLocationAndroidPlatformProvider::RequestAndroidPermissions()
{
	if (this->PermissionsHandler == nullptr)
	{
		this->PermissionsHandler = NewObject<UGeoAndroidPermissionHandler>();
		this->PermissionsHandler->world = GetWorld();
		this->PermissionsHandler->AddToRoot();
	}

	PermissionsBeingRequested = true;
	this->PermissionsHandler->Request();
}
