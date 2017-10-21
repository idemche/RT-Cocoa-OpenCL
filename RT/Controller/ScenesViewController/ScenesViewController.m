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

@property (weak) IBOutlet WebView        *octaWebView;
@property (weak) IBOutlet NSButton        *octaButton;
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
    
    
    //    _octaScene.canDrawSubviewsIntoLayer = YES;
    //    _octaScene.animates = YES;
    //    _octaScene.imageScaling = NSImageScaleNone;
    //    NSImageView *octa = [[NSImageView alloc] initWithFrame: CGRectMake(10, 10, 150, 113)];
    //    octa.imageScaling = NSImageScaleNone;
    //    octa.animates = YES;
    //    octa.image = [NSImage imageNamed:@"Octa"];
    //    octa.canDrawSubviewsIntoLayer = YES;
    //
    //    NSView *view = [[NSView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
    //    view.wantsLayer = YES;
    //    [view addSubview:octa];
    //
    //    [[self view] addSubview: view];
    
}

- (void)returnScene:(NSString*)map {
    
    NSString *bundleRoot = [[NSBundle mainBundle] bundlePath];
    InfoSingleton *manager = [InfoSingleton shared];
    
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
            if (!__builtin_strcmp([map cStringUsingEncoding:[NSString defaultCStringEncoding]], manager.information->scenes[i])) {
                manager.information->num_scene = i;
            }
            NSLog(@"Files in resource folder: %@", filename);
            i++;
        }
    }
}

-(void)viewDidDisappear {
    NSLog(@"Scenes are dead");
}

- (IBAction)didPressOctaScene:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"octahedron" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}

- (IBAction)didPressBhEnv:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"bh_env" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBocalEnv:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"bocal_env" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBocal:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"bocal" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBocuelipseEnv:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"bocuelipse_env" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBocuelipse:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"bocuelipse" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressBox:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"box" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressCubehole:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"cubehole" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressCubohedron:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"cubohedron" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressDisturbances:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"disturbances" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressDna:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"dna" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressDof:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"dof" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressEnvMapTorus:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"env_map_torus" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressEnvMap:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"env_map" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressExObj:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"ex_obj" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressLimitedObjects:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"limited_objects" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressMoebius:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"moebius" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressNegativeCheck:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"negative_check" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressParaboloid:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"paraboloid" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}

- (IBAction)didPressPyramid:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"pyramid" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
//++++++++++++
- (IBAction)didPressReflTransp:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"refl_transp" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressRgb:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"rgb" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressRing:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"ring" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressSphere:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"sphere" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressTetrahedron:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"tetrahedron" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressTextures:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"textures" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressTorusInsideSphere:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"torus_inside_sphere" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}
- (IBAction)didPressTorus:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"torus" ofType:@"json"];
    [self returnScene:_pathString];
    [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
}

@end
