//
//  VoidViewController.m
//  RT
//
//  Created by Heorhii Shakula on 15.10.17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "VoidViewController.h"

@interface VoidViewController ()


@end

@implementation VoidViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
	
	InfoSingleton *manager = [InfoSingleton shared];
	
    NSLog(@"%p", manager.information);
	manager.information->port = (char*)"4444";
	manager.information->tcp_port = 4242;
	server(manager.information);

    //
    // Do view setup here.
}

-(void)viewDidDisappear {
    
//    free((void*)_map_path);
//    free((void*)_port);
}

@end
