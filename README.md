# GeoLocation plugin for UE

## Status: Deprecated - See information below

This open source release is intended to allow anyone with existing UE
projects that use the plugin from the Marketplace to continue using it
as a project plugin. This can be done by putting a copy of the plugin
in a folder located at `Plugins/GeoLocation/` in the folder structure
of the project by either cloning this repository to that location, or
downloading then unarchiving the zip file found here:
https://github.com/stevenjt/GeoLocation/archive/refs/heads/master.zip

More information about plugins in projects can be found here:
https://docs.unrealengine.com/5.0/en-US/plugins-in-unreal-engine/#pluginsinprojects

By changing the `EngineVersion` value in `GeoLocation.uplugin` the
plugin should compile in versions of UE4 from the past few years. The
engine version is currently set to 5.0.0 and while it compiles in UE5,
it has not been tested on any devices using that version of Unreal
Engine.

## Description

GeoLocation provides components and tools that make developing geographically
aware features easier in Unreal Engine 4. It can be used from both Blueprint and
C++ with support for iOS and Android platforms. Geo location data will be as
accurate as possible given what each platform/device hardware allows.

When running in the Unreal Editor a set of global functions are included that
can set simulated data for testing and development.

Components for the plugin can be found in the Add Component menu for Blueprints
in the "GeoLocation" category. Global Blueprint functions can be found under the
"Geo Location" category when adding a new node to a Blueprint graph.

The headers for the components and static function classes are accessible to use
from C++.

Example project (Requires Microsoft Visual Studio to be installed):
https://www.dropbox.com/s/aspst9ks4xamtg2/GeoLocationExample-1.2.1.zip?dl=0

## Technical Details

This plugin contains a single module "GeoLocation" which contains components for
Geo Locations, Heading, Geo Fences and Distance Tracking. It also provides a set
of global functions for utility functions relating to geo location data and
setting platform specific settings for iOS and Android.

The components this plugin provides are GeoLocationComponent,
GeoLocationHeadingComponent, GeoFenceRectangleComponent,
GeoFenceCircleComponent, GeoFencePolygonComponent and
GeoDistanceTrackerComponent

Supported Platforms:
- iOS
- Android

iOS Specific Details:
- iOS 10 requires a description of how an app will use location data access (NSLocationWhenInUseUsageDescription in the Plist). The plugin automatically sets this in the project settings for iOS (Project Settings -> iOS -> AdditionalPlistData). New values for the description will be kept and not overwritten by the plugin.
