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

#ifndef TDNavOutput_h
#define TDNavOutput_h

@interface TDNavOutput : NSObject

/*! @brief Estimated latitude (degrees) */
@property (nonatomic) double latitude;

/*! @brief longitude Estimated longitude (degrees) */
@property (nonatomic) double longitude;

/*! @brief Estimated bearing (degrees) */
@property (nonatomic) double bearing;

/*! @brief Estimated magnetic heading (degrees) */
@property (nonatomic) double viewHeading;

/*! @brief Current floor */
@property (nonatomic) int floor;

/*! @brief Estimated error of location (meters) */
@property (nonatomic) double accuracyRadius;

/*! @brief Timestamp of the utc time the sample was processed (seconds since unix rollover on January 1, 1970 00:00:00 UTC) */
@property (nonatomic) double utc;

/*! @brief Estimated local frame x location (meters) */
@property (nonatomic) double x;

/*! @brief Estimated local frame y location (meters) */
@property (nonatomic) double y;

/*! @brief Estimated error of local frame estimated x location (meters) */
@property (nonatomic) double xFom;

/*! @brief Estimated error of local frame estimated y location (meters) */
@property (nonatomic) double yFom;

/*!
 Bitfield:
 
 ACCELEROMETER = 0x0001
 
 MAGNETOMETER = 0x0002
 
 GYROSCOPE = 0x0004
 
 BAROMETER = 0x0008
 
 GPS = 0x0010
 
 WIFI = 0x0020
 
 MAP_AIDING = 0x0040
 
 NFC = 0x0080
 
 WALL_CONSTRAINTS = 0x0400
 
 BLE = 0x0800
 */
@property (nonatomic) int usedSystems;

/*!
 Bitfield:
 
 xxxx xx00b = stationary (all bits must be zero)
 
 xxxx xx01b = minor motion detected
 
 xxxx xx10b = significant/major motion detected
 
 xxxx 01xxb = experiencing low sustained dynamics
 
 xxxx 10xxb = experiencing high sustained dynamics
 
 1111 1111b = unknown
 */
@property (nonatomic) int dynamicState;

/*!
 -1 = transitioning downward in pressure altitude
 
 1 = transitioning upward in pressure altitude
 
 0 = maintaining pressure altitude
 */
@property (nonatomic) double elevationState;

/*! @brief Boolean indicating whether or not the device is exceeding 25 mph */
@property (nonatomic) bool pdrSpeedLimitExceeded;

@end

#endif /* TDNavOutput_h */
