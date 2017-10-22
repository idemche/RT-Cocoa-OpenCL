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
#import "OperationsManager.h"
#import "rt.h"

@interface RenderViewController ()

@property (weak) IBOutlet NSButton *lightOutlet;
@property (weak) IBOutlet NSButton *indirectLight;
@property (weak) IBOutlet NSButton *parallelLight;
@property (weak) IBOutlet NSButton *spotLight;

@property (weak) IBOutlet NSPopUpButton *colorEffects;
@property (weak) IBOutlet NSPopUpButton *toneMappers;
@property (weak) IBOutlet NSPopUpButton *movementDistance;
@property (weak) IBOutlet NSPopUpButton *rotationAngle;
@property (weak) IBOutlet NSPopUpButton *movementFactor;
@property (weak) IBOutlet NSPopUpButton *rotationFactor;
@property (weak) IBOutlet NSPopUpButton *cameraMode;


@property (weak) IBOutlet NSTextField *apertureRadiusTextField;
@property (weak) IBOutlet NSTextField *focalLengthTextField;

@property (nonatomic, assign) int   didStart;

@end

@implementation RenderViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    _didStart = 0;
}

- (void)viewDidAppear {
	
    if (_didStart == 0) {
	
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
                i++;
            }
        }
        
        _didStart = 1;
        [self performSegueWithIdentifier: @"VoidViewController" sender: self];
    }
}

-(void)viewDidDisappear {
	
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
			[_parallelLight setEnabled: YES];
			[_spotLight setEnabled: YES];
			return;
			
		case 0:
			
			[_indirectLight setState: NSOffState];
			[_parallelLight setState: NSOffState];
			[_spotLight setState: NSOffState];

			[_indirectLight setEnabled: NO];
			[_parallelLight setEnabled: NO];
			[_spotLight setEnabled: NO];
			return;
	}
}

- (BOOL) validateDouble:(NSString *)value {
	
	NSLocale *locale = [NSLocale currentLocale];
	NSString *thousandSeparator = [locale objectForKey:NSLocaleGroupingSeparator];
	NSString *result = [value stringByReplacingOccurrencesOfString:thousandSeparator withString:@""];

	NSString *doubleRegex = @"[0-9]{1,6}(\\.[0-9]*)?";
	NSPredicate *doublePredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", doubleRegex];
	return [doublePredicate evaluateWithObject: result];
}

- (IBAction)didPressUpdateScene:(NSButton *)sender {
	
	InfoSingleton *manager = [InfoSingleton shared];
	
	NSString *one = [_apertureRadiusTextField stringValue];
	NSString *two = [_focalLengthTextField stringValue];
	
	if ([one length] == 0 || [two length] == 0)
	{
		[OperationsManager displayError: @"Empty fields" : @"Please fill all fields]"];
		return;
	}
	
	if (![self validateDouble: [_apertureRadiusTextField stringValue]]) {
		[OperationsManager displayError: @"Invalid aperture" : @"Please enter valid aperture [double value with 6 digits maximum length]"];
		return;
	} else if (![self validateDouble:[_focalLengthTextField stringValue]]) {
		[OperationsManager displayError: @"Invalid focal length" : @"Please enter valid focal length [double value with 6 digits maximum length]"];
		return;
	} else if ([_apertureRadiusTextField doubleValue] < 0 || [_focalLengthTextField doubleValue] < 5 ) {
		[OperationsManager displayError: @"Invalid values" : @"Does focal > 5 and does aperture > 0?]"];
		return;
	}

	//validateDoubleValue

	manager.information->keys.aperture = [_apertureRadiusTextField doubleValue];
	manager.information->keys.fl = [_focalLengthTextField doubleValue];
    manager.information->keys.light = [_lightOutlet state];
	manager.information->keys.c_mode = [_cameraMode indexOfSelectedItem];
	manager.information->keys.indirect_light = [_indirectLight state];
	manager.information->keys.parallel_light = [_parallelLight state];
	manager.information->keys.spot_light = [_spotLight state];
	manager.information->keys.visual_effect = [_colorEffects indexOfSelectedItem];
	manager.information->keys.tone_mapper = [_toneMappers indexOfSelectedItem];
	
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

@end
