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

#import <Foundation/Foundation.h>
#import "TDJSONSerializable.h"
@import CoreLocation;

@interface Location : NSObject <TDJSONSerializable>


@property (nonatomic) CLLocationCoordinate2D latLong;
@property (nonatomic) double x;
@property (nonatomic) double y;
@property (nonatomic) double z;
@property (nonatomic) double altitude;
@property (nonatomic) bool isGeo;


+ (NSArray *) fromJSONArray: (NSArray *) array;
+ (NSArray *) toJSONArray: (NSArray *) array;

/**
 * Parameterized constructor
 * @param a latitude (degrees) or X (meters)
 * @param b longitude (degrees) or Y (meters)
 * @param c elevation (meters) or Z (meters)
 * @param isGeo true if geographic (latitude/longitude/elevation), false if local (X/Y/Z)
 * @param refLat reference latitude for location
 * @param refLon reference longitude for location
 */
- (Location *) initWitha: (double) a b: (double) b c: (double) c isGeo: (bool) geo refLat: (double) refLat refLon: (double) refLon;
/**
 * Compute distance to another location
 * @param location location in degrees to compute distance
 * @return distance in meters
 */
- (double) distance: (CLLocationCoordinate2D) location;

- (double) getLatitude;
- (double) getLongitude;
- (void) setLatitude: (double) lat;
- (void) setLongitude: (double) lon;
- (void) convertToLocalWithRefLat: (double) latitude refLon: (double) longitude;

@end
