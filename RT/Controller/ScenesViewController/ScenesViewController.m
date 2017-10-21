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
@property (nonatomic, strong) NSString *pathString;
@property (nonatomic, assign) NSInteger index;

@end

@implementation ScenesViewController

@synthesize octaWebView = _octaWebView;
@synthesize pathString = _pathString;
@synthesize index = _index;

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

-(void)viewDidDisappear {
	NSLog(@"Scenes are dead");
}

- (IBAction)didPressOctaScene:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"octahedron" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 0;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}

- (IBAction)didPressBhEnv:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"bh_env" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 1;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBocalEnv:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"bocal_env" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 2;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBocal:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"bocal" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 3;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBocuelipseEnv:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"bocuelipse_env" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 4;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBocuelipse:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"bocuelipse" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 5;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBox:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"box" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 6;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressCubehole:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"cubehole" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 7;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressCubohedron:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"cubohedron" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 8;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressDisturbances:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"disturbances" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 9;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressDna:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"dna" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 10;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressDof:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"dof" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 11;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressEnvMapTorus:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"env_map_torus" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 12;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressEnvMap:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"env_map" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 13;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressExObj:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"ex_obj" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 14;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressLimitedObjects:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"limited_objects" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 15;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressMoebius:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"moebius" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 16;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressNegativeCheck:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"negative_check" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 17;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressParaboloid:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"paraboloid" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 18;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}

- (IBAction)didPressPyramid:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"pyramid" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 19;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
//++++++++++++
- (IBAction)didPressReflTransp:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"refl_transp" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 20;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressRgb:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"rgb" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 21;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressRing:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"ring" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 22;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressSphere:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"sphere" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 23;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressTetrahedron:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"tetrahedron" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 24;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressTextures:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"textures" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 25;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressTorusInsideSphere:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"torus_inside_sphere" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 26;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressTorus:(NSButton *)sender {
	_pathString = [[NSBundle mainBundle] pathForResource: @"torus" ofType:@"json"];
	((InfoSingleton*)[InfoSingleton shared]).information->num_scene = 27;
	[self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}

@end
