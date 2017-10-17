//
//  ClientStandbyViewController.h
//  RT
//
//  Created by Igor Demchenko on 10/12/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "DHCircularProgressView.h"
#import "rt.h"

@interface ClientStandbyViewController : NSViewController <NSWindowDelegate>

@property (nonatomic) const char *ip;
@property (nonatomic, assign) const int port;
@property (nonatomic, assign) const char isLast;
@property (weak) IBOutlet DHCircularProgressView *progressView;

@end
