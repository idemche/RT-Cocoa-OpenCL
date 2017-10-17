//
//  VoidViewController.m
//  RT
//
//  Created by Heorhii Shakula on 15.10.17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "VoidViewController.h"

@interface VoidViewController ()

@property (nonatomic, assign) const char *map_path;

@property (nonatomic, assign) const char *port;

@end

@implementation VoidViewController

@synthesize map_path = _map_path;
@synthesize port = _port;
@synthesize information = _information;

- (void)viewDidLoad {
    
    [super viewDidLoad];
    NSLog(@"%p", _information);
	_information->port = (char*)_port;
	_information->tcp_port = 4242;
	server(_information);

    //
    // Do view setup here.
}

-(void)viewDidDisappear {
    
//    free((void*)_map_path);
//    free((void*)_port);
}

@end
