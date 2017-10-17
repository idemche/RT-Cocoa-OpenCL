//
//  ClientStandbyViewController.m
//  RT
//
//  Created by Igor Demchenko on 10/12/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "ClientStandbyViewController.h"
#import "rt.h"

@interface ClientStandbyViewController ()

@property (nonatomic, assign) t_info *info;

@end

@implementation ClientStandbyViewController

@synthesize ip = _ip;
@synthesize port = _port;
@synthesize info = _info;
@synthesize isLast = _isLast;
@synthesize progressView = _progressView;

- (void)viewDidLoad {
	
	[super viewDidLoad];
	
	_info = (t_info*)malloc(sizeof(t_info));
	[_progressView setMaxValue: 100.0f];
	[_progressView setCurrentValue:0.0f];
	[_progressView setIncrementalSteps:[NSArray arrayWithObjects:[NSNumber numberWithDouble:25.0f], [NSNumber numberWithDouble:50.0f], [NSNumber numberWithDouble:75.0f], [NSNumber numberWithDouble:80.0f], nil]];

	[NSTimer scheduledTimerWithTimeInterval:1.0f/30.0f target:self selector:@selector(tick) userInfo:nil repeats:YES];
    //[window setStyleMask:[window styleMask] & ~NSResizableWindowMask];

	NSString *kernels = [[NSBundle mainBundle] pathForResource: @"kernels" ofType:@"lol"];
	
	_info->kernel_path = __builtin_strdup([kernels cStringUsingEncoding:[NSString defaultCStringEncoding]]);
    
    NSLog(@"%@", kernels);
    
//    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
//        client(_info, _ip, _port, _isLast);
//    });
    // Do view setup here.
}

- (BOOL)windowShouldClose:(id)sender {
	NSLog(@"Standby is closed");
	return false;
}

- (void)tick {
	
	if(_progressView.currentValue == _progressView.maxValue)
	{
		_progressView.currentValue = 0.0f;
	}
	
	[_progressView incrementBy:0.3f];
}

@end
