//
//  InfoSingleton.h
//  RT
//
//  Created by Igor Demchenko on 10/21/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "rt.h"

@interface InfoSingleton : NSObject

@property(atomic) t_info *information;
@property(nonatomic, assign) NSInteger serverIsInitiated;

+(id)shared;

@end
