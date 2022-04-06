/**
 * GeoLocation
 *
 * Copyright (c) 2016 Steven Thompson
**/

#include "GeoLocation.h"

#if PLATFORM_ANDROID
#include "GeoLocationAndroidPlatformProvider.h"
#elif defined PLATFORM_HTML5 && PLATFORM_HTML5
#include "GeoLocationHTML5PlatformProvider.h"
#elif PLATFORM_IOS
#include "GeoLocationIOSPlatformProvider.h"
#else
#include "GeoLocationEditorPlatformProvider.h"
#endif

#define LOCTEXT_NAMESPACE "FGeoLocationModule"

void FGeoLocationModule::StartupModule()
{
	this->AddIOSLocationWhenInUseDescriptionToPlist("GeoLocation requires access to location data");
	this->AddAndroidGooglePlayServicesVersionConfig();

	FWorldDelegates::OnWorldTickStart.AddRaw(this, &FGeoLocationModule::WorldTick);
}

void FGeoLocationModule::ShutdownModule()
{
	FWorldDelegates::OnWorldTickStart.RemoveAll(this);
}

FGeoLocationModule& FGeoLocationModule::Get()
{
	return FModuleManager::LoadModuleChecked<FGeoLocationModule>("GeoLocation");
}

AGeoLocationProvider* FGeoLocationModule::GetPlatformProvider(UWorld* world = nullptr)
{
	if (!this->GeoLocationProviderReady && world != nullptr)
	{
#if PLATFORM_ANDROID
		this->GeoLocationProvider = NewObject<AGeoLocationAndroidPlatformProvider>();
#elif defined PLATFORM_HTML5 && PLATFORM_HTML5
		this->GeoLocationProvider = NewObject<AGeoLocationHTML5PlatformProvider>();
#elif PLATFORM_IOS
		this->GeoLocationProvider = NewObject<AGeoLocationIOSPlatformProvider>();
#else
		this->GeoLocationProvider = NewObject<AGeoLocationEditorPlatformProvider>();
#endif
		// Stop Unreal from deleting the provider during garbage collection by adding it to the root set
		this->GeoLocationProvider->AddToRoot();

		this->GeoLocationProvider->Setup(world);
		this->GeoLocationProviderReady = true;
	}

	return this->GeoLocationProvider;
}

void FGeoLocationModule::ShutdownPlatformProvider()
{
	// Remove the provider from the root set so that Unreal can delete the instance during shutdown
	this->GeoLocationProvider->RemoveFromRoot();
	this->GeoLocationProviderReady = false;

	this->GeoFences().Empty();
}

TArray<UGeoFenceComponent*>& FGeoLocationModule::GeoFences()
{
	if (!GeoFencesReady)
	{
		_GeoFences = TArray<UGeoFenceComponent*>();
		GeoFencesReady = true;
	}

	return _GeoFences;
}

void FGeoLocationModule::AddIOSLocationWhenInUseDescriptionToPlist(FString usageDescription)
{
    FString additionalPlistDataContent;
	GConfig->GetString(TEXT("/Script/IOSRuntimeSettings.IOSRuntimeSettings"), TEXT("AdditionalPlistData"), additionalPlistDataContent, this->GetProjectDefaultEngineIniPath());

	// Only add the location usage description if a description does not already exist
	if (!additionalPlistDataContent.Contains(TEXT("NSLocationWhenInUseUsageDescription")))
	{
		additionalPlistDataContent.Append(TEXT("<key>NSLocationWhenInUseUsageDescription</key><string>") + usageDescription + TEXT("</string>\n"));
        
		GConfig->SetString(TEXT("/Script/IOSRuntimeSettings.IOSRuntimeSettings"), TEXT("AdditionalPlistData"), *additionalPlistDataContent, this->GetProjectDefaultEngineIniPath());
        GConfig->Flush(false, this->GetProjectDefaultEngineIniPath());
        
        // Additional Plist Data in the iOS Project Settings UI will not populate with the latest changes without also setting the value in GEngineIni
        GConfig->SetString(TEXT("/Script/IOSRuntimeSettings.IOSRuntimeSettings"), TEXT("AdditionalPlistData"), *additionalPlistDataContent, GEngineIni);
	}
}

void FGeoLocationModule::AddAndroidGooglePlayServicesVersionConfig()
{
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION < 17
	FString googlePlayServicesVersion = "9.2.0";
#elif ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION == 17
	FString googlePlayServicesVersion = "9.8.0";
#elif ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION <= 20
	FString googlePlayServicesVersion = "11.0.4";
#else
	FString googlePlayServicesVersion = "11.8.0";
#endif

	GConfig->SetString(TEXT("/Script/GeoLocation.GeoLocationSettings"), TEXT("AndroidGooglePlayServicesVersion"), *googlePlayServicesVersion, this->GetProjectDefaultEngineIniPath());
	GConfig->Flush(false, this->GetProjectDefaultEngineIniPath());
}

FString FGeoLocationModule::GetProjectDefaultEngineIniPath()
{
    FString projectDefaultEngineIni = TEXT("");
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION <= 17
    projectDefaultEngineIni = FPaths::GameConfigDir() / TEXT("DefaultEngine.ini");
#else
    projectDefaultEngineIni = FPaths::ProjectConfigDir() / TEXT("DefaultEngine.ini");
#endif
    return projectDefaultEngineIni;
}

void FGeoLocationModule::WorldTick(UWorld* world, ELevelTick tickType, float deltaTime)
{
	if (this->GeoLocationProviderReady)
	{
		this->GeoLocationProvider->CheckPermissions();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGeoLocationModule, GeoLocation)
