//
//  InfoSingleton.m
//  RT
//
//  Created by Igor Demchenko on 10/21/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "InfoSingleton.h"

@implementation InfoSingleton

+(id)shared {
	
	static InfoSingleton *shared = nil;
	static dispatch_once_t onceToken;
	dispatch_once(&onceToken, ^ {
		shared = [[self alloc] init];
	});
	return shared;
}

- (id)init {
	
	if (self == [super init]) {
		_information = (t_info*)malloc(sizeof(t_info));
        *_information = (t_info){0};
        _serverIsInitiated = 0;
	}
	return self;
}

- (void)dealloc {}

@end
