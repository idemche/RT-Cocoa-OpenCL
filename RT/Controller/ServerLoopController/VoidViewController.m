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
	
	server(manager.information);
	[super viewDidLoad];

    //
    // Do view setup here.
}

-(void)viewDidAppear {
	exit(1);
}

-(void)viewDidDisappear {
    
//    free((void*)_map_path);
//    free((void*)_port);
}

@end
