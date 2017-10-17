//
//  OperationsManager.m
//  RT
//
//  Created by Igor Demchenko on 10/12/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "OperationsManager.h"

@implementation OperationsManager

+(BOOL)IsEmpty: (id) thing {
	
	return thing == nil
	|| ([thing respondsToSelector:@selector(length)]
		&& [(NSData *)thing length] == 0)
	|| ([thing respondsToSelector:@selector(count)]
		&& [(NSArray *)thing count] == 0);
}

+(void)displayError: (NSString *)alertString : (NSString *)informativeString {
	
	NSAlert *alert = [[NSAlert alloc] init];
	
	[alert setMessageText: alertString];
	[alert setInformativeText: informativeString];
	[alert addButtonWithTitle:@"Cancel"];
	[alert addButtonWithTitle:@"Ok"];
	
	[alert runModal];
}

@end

