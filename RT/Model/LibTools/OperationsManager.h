//
//  OperationsManager.h
//  RT
//
//  Created by Igor Demchenko on 10/12/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface OperationsManager : NSObject

+(BOOL)IsEmpty: (id) thing;
+(void)displayError: (NSString *)alertString : (NSString *)informativeString;

@end
