//
//  ClientViewController.h
//  RT
//
//  Created by Macintosh OS X on 10.10.17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define CASE_AND(one, two)		if ([__o__ isEqualToString:(one)] && [__t__ isEqualToString:(two)])
#define CASE_OR(one, two)		if ([__o__ isEqualToString:(one)] || [__t__ isEqualToString:(two)])
#define SWITCH(o, t)			for (NSString *__o__ = (o) && NSString *__t__ = (t); ; )
#define DEFAULT

@interface ClientViewController : NSViewController <NSTextFieldDelegate>

@end
