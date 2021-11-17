/****************************************************************************
 *
 * Copyright (c) 2021 Inpixon, Inc. All rights reserved.
 *
 * This source is subject to the Inpixon Software License.
 * This software is protected by Copyright and the information and source code
 * contained herein is confidential. The software including the source code
 * may not be copied and the information contained herein may not be used or
 * disclosed except with the written permission of Inpixon, Inc.
 *
 * All other rights reserved.
 *
 * This code and information are provided "as is" without warranty of any
 * kind, either expressed or implied, including but not limited to the
 * implied warranties of merchantability and/or fitness for a
 * particular purpose.
 *
 ****************************************************************************/

@import CoreMotion;
@import CoreLocation;
@import CoreBluetooth;
@import QuartzCore;

#import <Foundation/Foundation.h>
#import "location.h"
#import "region.h"
#import "floor_plan.h"
#import "TDNavOutput.h"


NS_ASSUME_NONNULL_BEGIN

@class Extend;


#pragma mark - Extend Delegate

@protocol OnExtendDelegate <NSObject>

@required

/*!
 Called when the OnExtendDelegate is ready to report events.
 
 @param ready If true, the services are ready for use, else the system has timebombed.
 */
- (void)onReady:(bool)ready;

/*!
 Called when the registration query returns and the authentication key has been evaluated. If the key is valid, it's value is cached so that subsequent key validation attempts can be done without a network connection. This cached value is stored for up to ninety days. After ninety days, the query is repeated to ensure validity.
 
 It is recommended that you set Extend subsystems here and start the Extend service here as no Extend methods (outside of -setOnExtendDelegate:) will be executed until the key has been validated.
 
 @param validated True if the key is valid, false otherwise.
 */
- (void)onKeyValidation:(bool)validated;

/*!
 Called when a new navigation solution is available. This delegate reports at rate of 32 hz. The returned TDNavOutput object encapsulates all of the necessary navigation engine values.
 
 @param navOutput TDNavOutput object containing all of the relevant navigation data.
 */
- (void)onNavigationUpdate:(TDNavOutput *)navOutput;

@optional

/*!
 Called when the debug data has been updated.
 
 @warning This is used for testing purposes only. Do not base any critical functions of your application on this delegate as it's updated infrequently.
 @param data NSDictionary of internal debug data.
 */
- (void)onDebug:(NSDictionary *)data;

/**
 * Called in response to each log file uploading.
 *
 * @param percentage Percentage of uploaded files size to total files.
 * @param succeedFileCount Number of successfully uploaded logs.
 * @param failedFileCount Number of upload failed logs.
 * @param totalFileCount Number of all logs.
 */
- (void) onUploadProgressUpdate: (int) percentage succeed: (int) succeedFileCount failed: (int) failedFileCount total: (int) totalFileCount ;


/*!
 Called when you enter a new facility's bounding region, signifying this as the active facility. This is only called if it's the first time you enter a facility's bounding region or if you re-enter a facility after having been at another facility. If you only exit the facility's bounding region and re-enter the same facility's region without spending time at another facility, the -onRegionUpdateRegion: onRegionUpdateEntered: delegate will be called instead.
 
 @param name Name of the active facility (nullable).
 @param location Location of the active facility (nullable).
 @param region Bounding region of active facility (nullable).
 @param plans List of the floor plans of the active facility (nullable).
 @param categories Not used, will be removed in a future version.
 */
- (void)onFacilityUpdateName:(nullable NSString *)name onFacilityUpdateLocation:(nullable Location *)location onFacilityUpdateRegion:(nullable Region *)region onFacilityUpdateFloorPlans:(nullable NSArray *)plans onFacilityUpdateCategories:(nullable NSArray *)categories;


@end


@interface Extend : NSObject

/*!
 The Extend constructor that passes along the activation key, server URL, OnExtendDelegate delegate and image downloading enable option. This is a singleton so any attempt to recreate the Extend object is ignored.
 
 @param key Activation key required for validation (nonnull).
 @param url The server URL string (nullable). If a nil value is set, the default URL https://portal.tendegrees.net is used.
 @param delegate The implementation of OnExtendDelegate to be used (nullable). Setting this parameter to nil is not recommended as you will not receive any OnExtendDelegate events.
 @param enableImageDownloading Setting this parameter to true will enable image downloading.
 @return The Extend object.
 */
+ (Extend *)sharedExtendWithKey:(NSString *)key url:(NSString*)url delegate:(id<OnExtendDelegate>)delegate enableImageDownloading:(bool) enable;

/*!
 The preferred Extend constructor that passes along the activation key, server URL and OnExtendDelegate delegate. This is a singleton so any attempt to recreate the Extend object is ignored.
 
 @param key Activation key required for validation (nonnull).
 @param url The server URL string (nullable). If a nil value is set, the default URL https://portal.tendegrees.net is used.
 @param delegate The implementation of OnExtendDelegate to be used (nullable). Setting this parameter to nil is not recommended as you will not receive any OnExtendDelegate events.
 @return The Extend object.
 */
+ (Extend *)sharedExtendWithKey:(NSString *)key url:(nullable NSString*)url delegate:(nullable id<OnExtendDelegate>)delegate;


/*!
 Checks if any Extend service systems are running.
 
 @return True if any extend service systems are running (mobility, vicinity).
 */
- (bool)isServiceStarted;

/*!
 Start Extend and any other enabled sub-systems. Call [extend stop]; to stop the services.
 
 It's recommended you call this method after -onKeyValidation: has returned as the method will not be executed unless the authentication key has been validated.
 
 @return True if system is ready and authenticated, otherwise false.
 */
- (bool)start;

/*!
 Start Extend and any other enabled sub-systems at the specified location. Call [extend stop]; to stop the services.
 
 It's recommended you call this method after -onKeyValidation: has returned as the method will not be executed unless the authentication key has been validated.
 
 <pre>
 With this API, the sequence of location events used by navigation engine is below:
 1). Use gps or location from network whichever is returned by the device.
 2). If no gps or no location from network, SDK will use the preset values to start the SDK.
 </pre>
 
 @param lat The initial desired latitude (degrees).
 @param lon The initial desired longitude (degrees).
 @param floor The initial desired floor number.
 @return True if system is ready and authenticated, otherwise false.
 */
- (bool)startLat:(double)lat lon:(double)lon floor:(int)floor;

/*!
 Start Extend and any other enabled sub-systems at the specified location. Call [extend stop]; to stop the services.
 
 It's recommended you call this method after -onKeyValidation: has returned as the method will not be executed unless the authentication key has been validated.
 
 <pre>
 With this API, if type equals 1, the SDK will force the use of the preset values.
 If type equals 0, the sequence of location events used by navigation engine is below:
 1). Use gps or location from network whichever is returned by the device.
 2). If no gps or no location from network, SDK will use the preset values to start the SDK.
 </pre>
 
 @param lat The initial desired latitude (degrees).
 @param lon The initial desired longitude (degrees).
 @param floor The initial desired floor number.
 @param type 0 for normal start sequence, 1 to force the start position.
 @return True if system is ready and authenticated, otherwise false.
 */
- (bool)startLat:(double)lat lon:(double)lon floor:(int)floor type:(int)type;


/*!
 Stop all Extend and all active sub-systems. Call [extend start]; to restart these services.
 
 @return True if system is ready and authenticated, else false.
 */
- (bool)stop;



/*!
 Provides the floor for a CLLocation object returned from the guidance system callback as an int.
 
 @param location CLLocation object to get floor
 @return Floor of location as an int if found.
 */
- (int)getFloorForLocation:(CLLocation *)location;

/*!
 Checks if the Vicinity sub-system has been enabled.
 
 @return True if Vicinity is enabled, otherwise false.
 */
- (bool)isVicinityEnabled;


/*!
 Enables or disables the animation to smooth out the location update. Animation is disabled by default.
  
 @param enabled Set to true to enable or false to disable the animation.

 */
- (void)setAnimationEnabled:(bool)enabled;

/*!
 Enables or disables the Vicinity sub-system. Vicinity is disabled by default.
 
 It's recommended you call this method after -onKeyValidation: has returned as the method will not be executed unless the authentication key has been validated.
 
 @param enabled Set to true to enable or false to disable.
 @return True if system is ready and authenticated, otherwise false.
 */
- (bool)setVicinityEnabled:(bool)enabled;


/*!
 Returns an array of all of the facilities currently stored in the device's cache. The array is a list of these facility's filenames.
 
 @return List of facilities stored in the device's cache. If no facilities are currently stored, the array is empty.
 */
- (NSArray *)getFacilities;

/*!
 Pass in additional information to customize the navigation system.
 
 @warning Using this method may cause unforeseen results and therefore is not recommended. This is mainly used for debugging purposes only.
 
 @param debugDictionary NSDictionary object containing custom key/value pairs.
 @return True if the system is ready and authenticated, otherwise false.
 */
- (bool)debug:(NSDictionary *)debugDictionary;

/*!
 Debug support feature: uploading all logs to cloud.
 
 @return None.
 */
- (void)uploadLogs;

/*!
 Debug support feature: delete all logs.
 
 @return None.
 */
- (void)deleteLogs;



/*!
 Returns an NSDictionary containing Extend's version number and Navigation Engine's version number. The key name for the Extend version number is "ExtendSDKVersion" and the key name for the Navigation Engine number is "NavEngineVersion". The value's for these keys are string representations of the version numbers. This method is a class method.
 
 @return An NSDictionary of the Extend and Navigation Engine's current version numbers.
 */
+ (NSDictionary *)version;


/*!
 Turns logging of sensor data on or off (off by default).
 
 @param enabled True if you wish to log sensor data, false otherwise (false by default).
 @return True if the system is ready, otherwise false.
 */
- (bool)setLogWriting:(bool)enabled;

/*!
 Clears all Extend related cached items. This includes device settings parameters and last known location variables.
 */
- (void)clearMemory;

/*!
 Returns a Vicinity floorplan image for a specified filename as an NSData object.
 
 @param filename The filename of the floorplan image (nonnull).
 @return An NSData representation of the floorplan image if it exists. Returns nil if no image is found.
 */
- (NSData *)getVicinityImage:(nonnull NSString *)filename;

@end

NS_ASSUME_NONNULL_END

