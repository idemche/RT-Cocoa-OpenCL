//
//  RenderViewController.m
//  RT
//
//  Created by Macintosh OS X on 10.10.17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "RenderViewController.h"
#import "ScenesViewController.h"
#import "VoidViewController.h"
#import "SDL.h"
#import "rt.h"

@interface RenderViewController ()

@property (weak) IBOutlet NSButton *lightOutlet;
@property (weak) IBOutlet NSButton *depthOfField;
@property (weak) IBOutlet NSButton *indirectLight;
@property (weak) IBOutlet NSButton *parallelLight;
@property (weak) IBOutlet NSButton *spotLight;

@property (weak) IBOutlet NSPopUpButton *colorEffects;
@property (weak) IBOutlet NSPopUpButton *toneMappers;
@property (weak) IBOutlet NSPopUpButton *movementDistance;
@property (weak) IBOutlet NSPopUpButton *rotationAngle;

@end

@implementation RenderViewController

//@synthesize port = _port;
//@synthesize map_path = _map_path;
//@synthesize scene_index = _scene_index;
//@synthesize information = _information;
//@synthesize SCREEN_WIDTH = _SCREEN_WIDTH;
//@synthesize SCREEN_HEIGHT = _SCREEN_HEIGHT;

- (void)viewDidLoad {
    
    [super viewDidLoad];
}

- (void)viewDidAppear {
	
	InfoSingleton *manager = [InfoSingleton shared];
    
    ft_putstr("Server mode on\n");

	NSString *bundleRoot = [[NSBundle mainBundle] bundlePath];

	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSDirectoryEnumerator *direnum = [fileManager enumeratorAtPath:bundleRoot];
	NSString *filename;
	NSString *string;

	int i = 0;

	while ((filename = [direnum nextObject] )) {

		//change the suffix to what you are looking for
		if ([filename hasSuffix:@".json"] && i < 26) {

			// Do work here
			string = [NSString stringWithFormat:@"%@/%@", bundleRoot, filename];
			manager.information->scenes[i] = (char*)[string cStringUsingEncoding:[NSString defaultCStringEncoding]];
//			if (!__builtin_strcmp(_map_path, manager.information->scenes[i])) {
//				manager.information->num_scene = i;
//			}
			NSLog(@"Files in resource folder: %@", filename);
			i++;
		}
	}
	
    [self performSegueWithIdentifier: @"VoidViewController" sender: self];
}

-(void)viewDidDisappear {
	
    free((void*)_map_path);
    free((void*)_port);
}

- (IBAction)didPressLight:(NSButton *)sender {
	[self lightState: [_lightOutlet state]];
}

- (IBAction)didPressChangeScene:(NSButton *)sender {

	[self performSegueWithIdentifier: @"ShowScenes" sender: self];
}

-(void)lightState: (NSInteger)state {
	
	switch (state) {
			
		case 1:
			
			[_indirectLight setEnabled: YES];
			[_depthOfField setEnabled: YES];
			[_parallelLight setEnabled: YES];
			[_spotLight setEnabled: YES];
			return;
			
		case 0:
			
			[_indirectLight setState: NSOffState];
			[_depthOfField setState: NSOffState];
			[_parallelLight setState: NSOffState];
			[_spotLight setState: NSOffState];

			[_indirectLight setEnabled: NO];
			[_depthOfField setEnabled: NO];
			[_parallelLight setEnabled: NO];
			[_spotLight setEnabled: NO];
			return;
	}
}

- (IBAction)didPressUpdateScene:(NSButton *)sender {
	
	InfoSingleton *manager = [InfoSingleton shared];
    
    manager.information->keys.light = [_lightOutlet state];
	manager.information->keys.c_mode = [_depthOfField state];
	manager.information->keys.indirect_light = [_indirectLight state];
	manager.information->keys.parallel_light = [_parallelLight state];
	manager.information->keys.spot_light = [_spotLight state];
	manager.information->keys.visual_effect = [_colorEffects indexOfSelectedItem];
	manager.information->keys.tone_mapper = [_toneMappers indexOfSelectedItem];
    
    manager.information->keys.change_scene = -1;
	
	switch ([_movementDistance indexOfSelectedItem]) {
		
		case 0:
			
			manager.information->keys.scale_speed = 1.0;
			break;
			
		case 1:
			
			manager.information->keys.scale_speed = 0.5;
			break;
			
		case 2:
			
			manager.information->keys.scale_speed = 0.1;
			break;
			
		default:
			break;
	}
	
	
	switch ([_rotationAngle indexOfSelectedItem]) {
		
		case 0:
			
			manager.information->keys.scale_angle = 1.0;
			break;
			
		case 1:
			
			manager.information->keys.scale_angle = 0.5;
			break;
			
		case 2:
			
			manager.information->keys.scale_angle = 0.1;
			break;
		
		default:
			break;
	}
	
	manager.information->keys.update = 1;
}

- (IBAction)didPressQuit:(NSButton *)sender {
	
    ((InfoSingleton*)[InfoSingleton shared]).information->quit = 1;
}

-(void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
    
    if ([segue.identifier isEqualToString: @"VoidViewController"]) {
        
        RenderViewController *data = (RenderViewController *)segue.destinationController;
        
        data.port = _port;
        data.map_path = _map_path;;
	} else if ([segue.identifier isEqualToString: @"ShowScenes"]) {
	
		ScenesViewController *data = (ScenesViewController*)segue.destinationController;
		
		data.scene_index = _scene_index;
	}
}
@end
