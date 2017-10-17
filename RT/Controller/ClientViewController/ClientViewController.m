//
//  ClientViewController.m
//  RT
//
//  Created by Macintosh OS X on 10.10.17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "ClientViewController.h"
#import "ClientStandbyViewController.h"
#import "OperationsManager.h"

@interface ClientViewController ()

@property (weak) IBOutlet NSTextField *ipAdressField;
@property (weak) IBOutlet NSTextField *portField;
@property (weak) IBOutlet NSButton *lastClient;

@end

@implementation ClientViewController

@synthesize portField = _portField;
@synthesize lastClient = _lastClient;
@synthesize ipAdressField = _ipAdressField;

- (void)viewDidLoad {
	
	[super viewDidLoad];
    // Do view setup here.
}
- (IBAction)didPressConnect:(NSButton *)sender {
	
	char ip_valid	= (char)@([OperationsManager IsEmpty: _portField.stringValue]).integerValue;
	char port_valid	= (char)@([OperationsManager IsEmpty: _ipAdressField.stringValue]).integerValue;
	
	
	switch ((int)(ip_valid || port_valid)) {
			
		case YES:
			
			[OperationsManager displayError: @"Invalid parameters" : @"Please enter valid parameters"];
			break;
			
		case NO:
			
			[self performSegueWithIdentifier:@"ClientStandby" sender: self];
			break;
	}
}

-(void)viewWillDisappear {
	NSLog(@"%s", "Byebye ClientViewController");
}

-(void)prepareForSegue: (NSStoryboardSegue *)segue sender: (id)sender {
	
	NSString *port	= _portField.stringValue;
	NSString *ip	= _ipAdressField.stringValue;
	
	if ([segue.identifier isEqualToString:@"ClientStandby"]) {
		
		ClientStandbyViewController *data = (ClientStandbyViewController*)segue.destinationController;
		
		data.ip = __builtin_strdup([ip cStringUsingEncoding: [NSString defaultCStringEncoding]]);
		data.port = (int)[port integerValue];
		data.isLast = _lastClient.state;
		[self removeFromParentViewController];
		
		NSArray<NSWindow *> *windows = NSApplication.sharedApplication.windows;
		
		for (NSWindow *window in windows) {
			
			if ([[window.contentViewController className] isEqualToString: @"ViewController"]) {
				[window close];
			}
		}
	}
}

@end
