//
//  iATLocation.mm
//  AKATSUKI
//
//  Created by Slowhand0309
//  Copyright © 2016年 Slowhand0309. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iATLocation.h"

/**
 * Get application bundle path.
 *
 * @return path
 */
const char *getApplicationRoot() {
    NSString *strPath = [[NSBundle mainBundle] bundlePath];
    return [strPath UTF8String];
}

/**
 * Get Document path.
 *
 * @return path
 */
const char *getDocumentRoot() {
    NSString *strPath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
    return [strPath UTF8String];
}
