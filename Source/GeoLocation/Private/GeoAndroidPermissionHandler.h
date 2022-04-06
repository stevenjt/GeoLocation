/**
 * GeoLocation
 *
 * Copyright (c) 2019 Steven Thompson
**/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Async/Async.h"

#include "GeoLocation.h"
#include "GeoLocationEnums.h"

#if PLATFORM_ANDROID
#include "AndroidPermissionFunctionLibrary.h"
#include "AndroidPermissionCallbackProxy.h"
#endif

#include "GeoAndroidPermissionHandler.generated.h"

/**
 * Geo Android Permission Handler
 */
UCLASS()
class UGeoAndroidPermissionHandler : public UObject
{
	GENERATED_BODY()
	
public:

	/**
	 * OnPermissionsGranted
	 */
	UFUNCTION()
	void OnPermissionsGranted(const TArray<FString> &permissions, const TArray<bool>& granted);

	void Request();

	/* UWorld reference */
	UPROPERTY()
		UWorld* world;

};
