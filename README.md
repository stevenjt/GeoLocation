# GeoLocation

## Description

Video: https://www.youtube.com/watch?v=-sXg2YVEID0

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

## Support

For support with the plugin you can email me at contact@stevenjt.com
