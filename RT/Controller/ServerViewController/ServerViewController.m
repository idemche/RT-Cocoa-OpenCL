//
//  ServerViewController.m
//  RT
//
//  Created by Macintosh OS X on 10.10.17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "ServerViewController.h"
#import "RenderViewController.h"
#import "OperationsManager.h"
#import "rt.h"

@interface ServerViewController ()

@property(nonatomic, readonly) int SCREEN_HEIGHT;
@property(nonatomic, readonly) int SCREEN_WIDTH;
@property(nonatomic, strong) NSString *path;
@property (weak) IBOutlet NSTextField *portField;
@property (weak) IBOutlet NSPopUpButton *mapSelection;
@property (weak) IBOutlet NSPopUpButton *resolutionPopUP;

@end

@implementation ServerViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    _SCREEN_HEIGHT = 480;
    _SCREEN_WIDTH = 480;
}

- (IBAction)didPressButton:(NSButton *)sender {
	
	int item = (int)[_resolutionPopUP indexOfSelectedItem];
	char port_field	= (char)@([OperationsManager IsEmpty: _portField.stringValue]).integerValue;
	_path = [self searchObjectPath];
	char *scene = (char*)[_path cStringUsingEncoding:[NSString defaultCStringEncoding]];
	
	switch (item) {
		
		case 4:
		
			_SCREEN_WIDTH = 1920;
			_SCREEN_HEIGHT = 1080;
		case 3:
			_SCREEN_WIDTH = 1920;
			_SCREEN_HEIGHT = 1080;
		
		default:
			_SCREEN_WIDTH = 800;
			_SCREEN_HEIGHT = 800;
	}

    if (port_field || validate_scene(scene))
        [OperationsManager displayError: @"Empty parameters" : @"Please enter valid parameters"];
    else
    {
		[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
}

-(void)viewWillDisappear {
	
	NSLog(@"%s", "Byebye ServerViewController");
}

-(void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
	
	if ([segue.identifier isEqualToString: @"ShowRenderer"]) {
        
        NSArray<NSWindow*> *windows = NSApplication.sharedApplication.windows;
        
        for (NSWindow *to_close in windows) {
            
            NSString *str = [to_close className];
            
            SWITCH (str) {
                
                CASE (@"SDLWindow") {
                    
                    break;
                }
                
                DEFAULT {
                    
                    [to_close close];
                    break;
                }
            }
        }
		
		RenderViewController *data = (RenderViewController *)segue.destinationController;
		
		const char *map_path = [_path cStringUsingEncoding:[NSString defaultCStringEncoding]];
		const char *port = [_portField.stringValue cStringUsingEncoding:[NSString defaultCStringEncoding]];
		
		data.port = __builtin_strdup(port);
		data.map_path = __builtin_strdup(map_path);
		data.SCREEN_WIDTH = _SCREEN_WIDTH;
		data.SCREEN_HEIGHT = _SCREEN_HEIGHT;
		 [self removeFromParentViewController];
		
    }
}

-(NSString*)searchObjectPath {
	
	NSString *pathString;
	
	switch ([_mapSelection indexOfSelectedItem]) {
		case 1:
			pathString = @"paraboloid";
			break;
		case 2:
			pathString = @"bh";
			break;
		case 3:
			pathString = @"bocuelipse_env";
			break;
		case 4:
			pathString = @"refl_transp";
			break;
		case 5:
			pathString = @"limited_objects";
			break;
		case 6:
			pathString = @"dna";
			break;
		case 7:
			pathString = @"bocuelipse";
			break;
		case 8:
			pathString = @"disturbances";
			break;
		case 9:
			pathString = @"negative_check";
			break;
		case 10:
			pathString = @"ex_obj";
			break;
		case 11:
			pathString = @"tetrahedron";
			break;
		case 12:
			pathString = @"octahedron";
			break;
		case 13:
			pathString = @"bocal_env";
			break;
		case 14:
			pathString = @"textures";
			break;
		case 15:
			pathString = @"env_map_torus";
			break;
		case 16:
			pathString = @"cubehole";
			break;
		case 17:
			pathString = @"solar";
			break;
		case 18:
			pathString = @"sphere";
			break;
		case 19:
			pathString = @"cubohedron";
			break;
		case 20:
			pathString = @"env_map";
			break;
		case 21:
			pathString = @"heart";
			break;
		case 22:
			pathString = @"moebius";
			break;
		case 23:
			pathString = @"box";
			break;
		case 24:
			pathString = @"rgb";
			break;
		case 25:
			pathString = @"bocal";
			break;
		default:
			pathString = @"torus";
			break;
	}
	
	NSString *path = [[NSBundle mainBundle] pathForResource: pathString ofType:@"json"];
	
	return path;
}

@end
