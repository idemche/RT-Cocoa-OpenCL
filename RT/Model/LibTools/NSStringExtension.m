//
//  NSStringExtension.m
//  RT
//
//  Created by Igor Demchenko on 10/13/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "NSStringExtension.h"

#include <arpa/inet.h>

@implementation NSString (IPValidation)

- (BOOL)isValidIPAddres {
	
	const char *utf8 = [self UTF8String];
	int success;
	
	struct in_addr dst;
	success = inet_pton(AF_INET, utf8, &dst);
	if (success != 1) {
		struct in6_addr dst6;
		success = inet_pton(AF_INET6, utf8, &dst6);
	}
	
	return success == 1;
}

@end
