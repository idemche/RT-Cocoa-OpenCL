//
//  ScenesViewController.m
//  RT
//
//  Created by Igor Demchenko on 10/16/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "ScenesViewController.h"
#import <Quartz/Quartz.h>


@interface ScenesViewController ()

@property (weak) IBOutlet WebView		*octaWebView;
@property (weak) IBOutlet NSButton		*octaButton;


@end

@implementation ScenesViewController

@synthesize octaWebView = _octaWebView;

- (void)viewDidLoad {
	
	[super viewDidLoad];
	
	dispatch_queue_t async_animation = dispatch_queue_create("animation", NULL);
	
	dispatch_async(async_animation, ^{
		NSString *path = [[NSBundle mainBundle] pathForResource:@"octa" ofType:@"html"];
		NSURL *url = [NSURL fileURLWithPath:path];
		[[_octaWebView mainFrame] loadRequest:[NSURLRequest requestWithURL:url]];
	});
	

//	_octaScene.canDrawSubviewsIntoLayer = YES;
//	_octaScene.animates = YES;
//	_octaScene.imageScaling = NSImageScaleNone;
//	NSImageView *octa = [[NSImageView alloc] initWithFrame: CGRectMake(10, 10, 150, 113)];
//	octa.imageScaling = NSImageScaleNone;
//	octa.animates = YES;
//	octa.image = [NSImage imageNamed:@"Octa"];
//	octa.canDrawSubviewsIntoLayer = YES;
//
//	NSView *view = [[NSView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
//	view.wantsLayer = YES;
//	[view addSubview:octa];
//
//	[[self view] addSubview: view];

}

- (IBAction)didPressOctaScene:(NSButton *)sender {
	NSLog(@"This scene is chosen");
}



-(void)viewDidDisappear {
}

@end
