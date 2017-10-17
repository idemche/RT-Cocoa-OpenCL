//
//  RenderViewController.h
//  RT
//
//  Created by Macintosh OS X on 10.10.17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "RenderViewController.h"
#import "VoidViewController.h"
#import "SDL.h"
#import "rt.h"

@interface RenderViewController : NSViewController

@property (nonatomic, assign) const char *port;
@property (nonatomic, assign) const char *map_path;
@property(atomic, assign) t_info *information;
@property(nonatomic, assign) int SCREEN_HEIGHT;
@property(nonatomic, assign) int SCREEN_WIDTH;
@property(nonatomic, assign) short	*scene_index;

@end
