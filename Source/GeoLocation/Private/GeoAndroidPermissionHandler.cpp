/**
 * GeoLocation
 *
 * Copyright (c) 2019 Steven Thompson
**/

#include "GeoAndroidPermissionHandler.h"

void UGeoAndroidPermissionHandler::Request()
{
	TArray<FString> permissions;
	permissions.Add(FString("android.permission.ACCESS_FINE_LOCATION"));

#if PLATFORM_ANDROID
	UAndroidPermissionCallbackProxy::GetInstance()->OnPermissionsGrantedDynamicDelegate.AddDynamic(this, &UGeoAndroidPermissionHandler::OnPermissionsGranted);
	UAndroidPermissionFunctionLibrary::AcquirePermissions(permissions);
#endif
}

void UGeoAndroidPermissionHandler::OnPermissionsGranted(const TArray<FString> &permissions, const TArray<bool>& granted)
{
#if PLATFORM_ANDROID
	UAndroidPermissionCallbackProxy::GetInstance()->OnPermissionsGrantedDynamicDelegate.RemoveDynamic(this, &UGeoAndroidPermissionHandler::OnPermissionsGranted);
#endif

	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		FGeoLocationModule::Get().GetPlatformProvider(this->world)->OnPermissionsGranted(permissions, granted);
	});
}
