/****************************************************************************
 *
 * Copyright (c) 2021 Inpixon, Inc. All rights reserved.
 *
 * This source is subject to the Inpixon Software License.
 * This software is protected by Copyright and the information and source code
 * contained herein is confidential. The software including the source code
 * may not be copied and the information contained herein may not be used or
 * disclosed except with the written permission of Ten Degrees, Inc.
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

@protocol TDJSONSerializable <NSObject>

/**
 * @param array not guaranteed to be of type dictionary
 * @return object instantiated from array
 */
+ (NSArray *) fromJSONArray: (NSArray *)array;

/**
 * @param array not guaranteed to be of type dictionary
 * @return object instantiated from array
 */
+ (NSArray *) toJSONArray: (NSArray *)array;

/**
 * @param dictionary not guaranteed to be of type dictionary
 * @return object instantiated from dictionary
 */
- (id) initWithJSONObject: (NSDictionary *) dictionary;

/**
 * @return dictionary corresponding to the object
 */
- (NSDictionary *) getJSONObject;

@end
